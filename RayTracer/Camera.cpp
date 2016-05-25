#include "Camera.h"
#include <iostream>
#include <stdexcept>
#include "Sphere.h"
#include "MathConstant.h"
#include "shared_ptr.h"


const int MAX_DEPTH = 5;  // 最大递归次数


Camera::Camera(const Vec3f &viewPoint, const Vec3f &viewDirection, const Vec3f &headDirection, const float verticalFOV, const float distanceFromEye2Image, const unsigned imageWidth, const unsigned imageHeight)
    :_viewPoint(viewPoint)
{
    // 方向向量的长度必须大于0
    if (viewDirection.norm() == 0 || headDirection.norm() == 0)
    {
        throw std::runtime_error("Norm of direction must not be equal to 0!");
    }

    // 视野角必须大于0小于90
    if (verticalFOV <= 0 || verticalFOV >= 90)
    {
        throw std::runtime_error("FOV must not be under 0 or above 90!");
    }

    // 眼睛到像面的距离必须大于0
    if (verticalFOV <= 0 || verticalFOV >= 90)
    {
        throw std::runtime_error("Distance from eye to image must not be under or equal to 0!");
    }

    // 图像尺寸必须大于0
    if (imageWidth <= 0 || imageHeight <= 0)
    {
        throw std::runtime_error("Size of image must not be under or equal to 0!");
    }

    _viewDirection = viewDirection;
    _viewDirection.normalize();
    _headDirection = headDirection;
    _headDirection.normalize();
    _verticalFOV = verticalFOV;
    _distanceFromEye2Image = distanceFromEye2Image;
    _imageWidth = imageWidth;
    _imageHeight = imageHeight;
    _image = cv::Mat(imageHeight, imageWidth, CV_8UC3);
}


// 单条光线跟踪
// ray: 光线
// scene: 场景
// depth: 最大递归次数
// 返回该光线收集到的颜色
Vec3f trace(const Ray &ray, const Scene &scene, const int depth)
{
    if(depth >= MAX_DEPTH)
    {
        return scene.backgroundColor();
    }

    float tNearest = INFINITY;  // 光线与第1个遇到的几何体相遇时对应的光线时刻
    const std::vector<const shared_ptr<Geometry> > geometries = scene.geometries();
    shared_ptr<Geometry> geometry(NULL);  // 光线第1个遇到的几何体

    Vec3f intersectionNormal(0.0, 0.0, 0.0);  // 光线与第1个遇到的几何体的交点处的法向量
    Vec3f intersectionNormalTemp(0.0, 0.0, 0.0);
    Vec3f intersectionColor(0.0, 0.0, 0.0);  // 光线与第1个遇到的几何体的交点处的颜色
    Vec3f intersectionColorTemp(0.0, 0.0, 0.0);

    // 计算第1个遇到的几何体
    for(unsigned i = 0; i < geometries.size(); i++)
    {
        float t = geometries[i]->intersect(ray, intersectionNormalTemp, intersectionColorTemp);
        if(t > 0 && t < tNearest)
        {
            tNearest = t;
            intersectionNormal = intersectionNormalTemp;
            intersectionColor = intersectionColorTemp;
            geometry = geometries[i];
        }
    }

    // 如果这条光线没有遇到任何几何体，则返回场景的背景光颜色
    if(!geometry)
    {
        return scene.backgroundColor();
    }

    intersectionNormal.normalize();

    Vec3f surfaceColor(0.0, 0.0, 0.0);  // 光线收集到的颜色

    Vec3f intersectionPoint = ray.pointAt(tNearest);  // 光线与第1个遇到的几何体的交点

    float bias = 1e-4;  // 定义一个稍大于0的bias，避免对象对自己投射阴影

    // 判断光线是否在几何体内部，如果在内部则将法向量翻转作为光线反射定律的法线
    bool inside = false;
    if(ray.direction().dot(intersectionNormal) > 0)
    {
        intersectionNormal *= -1;
        inside = true;
    }

    // 如果是光源 TODO
    if (geometry->isLight())
    {
        return geometry->emissionColor();
    }

    // 计算菲涅尔定律
    float facingRatio = (-1) * ray.direction().dot(intersectionNormal);
    float mix = 0.1;
    float fresnelEffect = 1 * mix + pow(1.0 - facingRatio, 3) * (1 - mix);

    // 计算镜面反射光线
    Vec3f nextSpecular(0.0, 0.0, 0.0);
    if(geometry->specular() > 0)
    {
        Vec3f reflectDirection = ray.direction() - intersectionNormal * 2 * ray.direction().dot(intersectionNormal);
        reflectDirection.normalize();
        nextSpecular = trace(Ray(intersectionPoint + intersectionNormal * bias, reflectDirection), scene, depth + 1) * geometry->specular();
    }

    // 计算折射光线
    Vec3f nextRefraction(0.0, 0.0, 0.0);
    if(geometry->transparency() > 0)
    {
        float ior = 1.1;  // 折射率 TODO 此处折射率固定，如果方便的话将折射率添加为Geometry类的属性之一
        float eta = inside ? ior : 1.0/ior;  // 如果入射光线在几何体内部，则折射率转为倒数
        float cosin = (-1) * intersectionNormal.dot(ray.direction());
        float k = 1 - eta * eta * (1 - cosin * cosin);
        Vec3f refractionDirection = ray.direction() * eta + intersectionNormal * (eta * cosin - sqrt(k));
        refractionDirection.normalize();
        nextRefraction = trace(Ray(intersectionPoint - intersectionNormal * bias, refractionDirection), scene, depth + 1) * geometry->transparency();
    }

    // 光线颜色是反射光线和折射光线的贡献总和
    surfaceColor += (nextSpecular * fresnelEffect + nextRefraction * (1 - fresnelEffect));

    // 计算漫反射
    Vec3f diffuse(0.0, 0.0, 0.0);
    if(geometry->diffuse() > 0)
    {
        // 计算场景中所有光源在该漫反射点贡献的光之和
        for(unsigned i = 0; i < geometries.size(); i++)
        {
            if(geometries[i]->isLight())  // 如果是光源
            {
                // 光源只能是Sphere类型的Geometry
                const Sphere *light = dynamic_cast<const Sphere *>(geometries[i].get());  // 此处用原始指针是因为如果使用shared_ptr的话后面会将Sphere错误地析构
                if (!light)
                {
                    throw std::runtime_error("Light must not be Geometry which is not Sphere!");
                }

                Vec3f transmission(1.0, 1.0, 1.0);
                Vec3f lightDirection = light->center() - intersectionPoint;
                lightDirection.normalize();

                // 检查和光源之间是否有遮挡，以达到阴影效果
                for(unsigned j = 0; j < geometries.size(); ++j)
                {
                    if(i != j)
                    {
                        if(geometries[j]->intersect(Ray(intersectionPoint + intersectionNormal * bias, lightDirection)) > 0)
                        {
                            // 若有几何图形遮挡并且该几何图形透明，则根据透明度计算透射系数
                            transmission = (transmission.array() * geometries[j]->surfaceColor().array()).matrix() * geometries[j]->transparency();  // 因为不允许在透明几何图形上贴纹理，所以此处直接用几何图形的表面颜色属性
                        }
                    }
                }                

                // 如果光源在交点处的背面，则该光源在此处光照为0
                surfaceColor += (transmission.array() * geometries[i]->emissionColor().array()).matrix() * std::max(float(0), intersectionNormal.dot(lightDirection)) * geometry->diffuse();
            }
        }

        // 背景光在该漫反射点贡献的光 TODO
//         surfaceColor += scene.backgroundColor() * 0.2 * geometry->diffuse();
    }

    return (surfaceColor.array() * intersectionColor.array()).matrix() + geometry->emissionColor();
}


const cv::Mat & Camera::render(const Scene &scene)
{
    const float invWidth = 1 / float(_imageWidth), invHeight = 1 / float(_imageHeight);
    const float aspectRatio = _imageWidth / float(_imageHeight);
    const float imageRealHeightHalf = tan(PI * 0.5 * _verticalFOV / 180.0) * _distanceFromEye2Image;  // 图像半高的实际长度

    // 对每个像素点进行光线跟踪
#pragma omp parallel for
    for(int row = 0; row < _imageHeight; row++)
    {
        for(int col = 0; col < _imageWidth; col++)
        {
            // 以图像中心点为坐标原点，宽为x轴，高为y轴时，该像素点的x、y坐标
            float x = (2 * ((col + 0.5) * invWidth) - 1) * imageRealHeightHalf * aspectRatio;
            float y = (1 - 2 * ((row + 0.5) * invHeight)) * imageRealHeightHalf;

            // 计算该像素点的真实三维坐标
            Vec3f xx = _viewDirection.cross(_headDirection) * x;
            Vec3f yy = _headDirection * y;
            Vec3f pixelCoordinate = _viewPoint + _viewDirection * _distanceFromEye2Image + xx + yy;  // 该像素点的真实三维坐标

            Vec3f pixel = trace(Ray(_viewPoint, pixelCoordinate - _viewPoint), scene, 0);
            for (unsigned i = 0; i < 3; i++)
            {
                _image.at<cv::Vec3b>(row, col)[i] = (unsigned char)(std::min(float(1), pixel[2 - i]) * 255);
            }
        }
    }

    return _image;
}
