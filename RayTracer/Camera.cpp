#include "Camera.h"
#include <iostream>
#include "Sphere.h"


const float PI = 3.141592653589;  // 圆周率
const float INFINITY = 1e8;  // 最大数值
const int MAX_DEPTH = 5;  // 最大递归次数


Camera::Camera(const Vec3f &viewPoint, const Vec3f &viewDirection, const Vec3f &headDirection, const float verticalFOV, const float distanceFromEye2Image, const unsigned imageWidth, const unsigned imageHeight)
    :_viewPoint(viewPoint)
    ,_viewDirection(viewDirection * (1.0 / viewDirection.length()))
    ,_headDirection(headDirection * (1.0 / headDirection.length()))
    ,_verticalFOV(verticalFOV)
    ,_distanceFromEye2Image(distanceFromEye2Image)
    ,_imageWidth(imageWidth)
    ,_imageHeight(imageHeight)
    ,_image(cv::Mat(imageHeight, imageWidth, CV_8UC3))
{
}


// 单条光线跟踪
// ray: 光线
// scene: 场景
// depth: 最大递归次数
// 返回该光线收集到的颜色
Vec3f trace(const Ray &ray, const Scene &scene, const int depth)
{
    float tNearest = INFINITY;  // 光线与第1个遇到的几何体相遇时对应的光线时刻
    const std::vector<Geometry *> geometries = scene.geometries();
    const Geometry *geometry = NULL;  // 光线第1个遇到的几何体

    Vec3f intersectionNormal(0.0, 0.0, 0.0);  // 光线与第1个遇到的几何体的交点处的法向量
    Vec3f intersectionNormalTemp(0.0, 0.0, 0.0);

    // 计算第1个遇到的几何体
    for(unsigned i = 0; i < geometries.size(); i++)
    {
        float t = geometries[i]->intersect(ray, intersectionNormalTemp);
        if(t > 0 && t < tNearest)
        {
            tNearest = t;
            intersectionNormal = intersectionNormalTemp;
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

    // 跟踪反射和折射光线
    if((geometry->transparency() > 0 || geometry->reflection() > 0) && depth < MAX_DEPTH)
    {
        // 计算菲涅尔定律
        float facingRatio = (-1) * ray.direction().dot(intersectionNormal);
        float mix = 0.1;
        float fresnelEffect = 1 * mix + pow(1.0 - facingRatio, 3) * (1 - mix);

        // 反射光线
        Vec3f reflectDirection = ray.direction() - intersectionNormal * 2 * ray.direction().dot(intersectionNormal);
        reflectDirection.normalize();
        Vec3f nextReflection = trace(Ray(intersectionPoint + intersectionNormal * bias, reflectDirection), scene, depth + 1);

        // 折射光线
        Vec3f nextRefraction = 0;
        if(geometry->transparency())  // 只有该几何体是透明的时候，才存在折射光线并跟踪之
        {
            float ior = 1.1;  // 折射率 TODO 此处折射率固定，如果方便的话将折射率添加为Geometry类的属性之一
            float eta = inside ? ior : 1.0/ior;  // 如果入射光线在几何体内部，则折射率转为倒数
            float cosin = (-1) * intersectionNormal.dot(ray.direction());
            float k = 1 - eta * eta * (1 - cosin * cosin);
            Vec3f refractionDirection = ray.direction() * eta + intersectionNormal * (eta * cosin - sqrt(k));
            refractionDirection.normalize();
            nextRefraction = trace(Ray(intersectionPoint - intersectionNormal * bias, refractionDirection), scene, depth + 1);
        }

        // 光线颜色是反射光线和折射光线的贡献总和
        surfaceColor = (nextReflection * fresnelEffect + nextRefraction * (1 - fresnelEffect) * geometry->transparency()) * geometry->surfaceColor();
    }
    else  // 如果该几何体表面是漫反射材质或是光源，则不需要继续跟踪光线
    {

        if (false)  //geometry->emissionColor().x > 0)  // 如果是光源 TODO
        {
            surfaceColor = geometry->emissionColor();
        } 
        else  // 如果是表面是漫反射材质的几何体
        {
            // 计算场景中所有光源在该漫反射点贡献的光之和
            for(unsigned i = 0; i < geometries.size(); i++)
            {
                if(geometries[i]->emissionColor().x > 0)  // 如果是光源
                {
                    // 光源只能是Sphere类型的Geometry
                    const Sphere *light = dynamic_cast<const Sphere *>(geometries[i]);
                    if (!light)
                    {
                        throw std::runtime_error("Light must not be Geometry which is not Sphere!");
                    }

                    float transmission = 1.0;
                    Vec3f lightDirection = light->center() - intersectionPoint;
                    lightDirection.normalize();

                    // 检查和光源之间是否有遮挡，以达到阴影效果
                    for(unsigned j = 0; j < geometries.size(); ++j)
                    {
                        if(i != j)
                        {
                            if(geometries[j]->intersect(Ray(intersectionPoint + intersectionNormal * bias, lightDirection)) > 0)
                            {
                                transmission = 0.0;
                                break;
                            }                        
                        }
                    }                

                    // 如果光源在交点处的背面，则该光源在此处光照为0
                    surfaceColor += geometry->surfaceColor() * transmission * std::max(float(0), intersectionNormal.dot(lightDirection)) * geometries[i]->emissionColor();
                }
            }
        }

    }

    return surfaceColor + geometry->emissionColor();
}


const cv::Mat & Camera::render(const Scene &scene)
{
    float invWidth = 1 / float(_imageWidth), invHeight = 1 / float(_imageHeight);
    float aspectRatio = _imageWidth / float(_imageHeight);
    float imageRealHeightHalf = tan(PI * 0.5 * _verticalFOV / 180.0) * _distanceFromEye2Image;  // 图像半高的实际长度

    // 对每个像素点进行光线跟踪
    for(unsigned row = 0; row < _imageHeight; row++)
    {
        for(unsigned col = 0; col < _imageWidth; col++)
        {
            // 以图像中心点为坐标原点，宽为x轴，高为y轴时，该像素点的x、y坐标
            float x = (2 * ((col + 0.5) * invWidth) - 1) * imageRealHeightHalf * aspectRatio;
            float y = (1 - 2 * ((row + 0.5) * invHeight)) * imageRealHeightHalf;

            // 计算该像素点的真实三维坐标
            Vec3f xx = _viewDirection.cross(_headDirection) * x;
            Vec3f yy = _headDirection * y;
            Vec3f pixelCoordinate = _viewPoint + _viewDirection * _distanceFromEye2Image + xx + yy;  // 该像素点的真实三维坐标

            Vec3f pixel = trace(Ray(_viewPoint, pixelCoordinate - _viewPoint), scene, 0);
            _image.at<cv::Vec3b>(row, col)[0] = (unsigned char)(std::min(float(1), pixel.z) * 255);
            _image.at<cv::Vec3b>(row, col)[1] = (unsigned char)(std::min(float(1), pixel.y) * 255);
            _image.at<cv::Vec3b>(row, col)[2] = (unsigned char)(std::min(float(1), pixel.x) * 255);
        }
    }

    return _image;
}
