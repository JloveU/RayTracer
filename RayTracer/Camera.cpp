#include "Camera.h"
#include <iostream>
#include <stdexcept>
#include "Sphere.h"
#include "MathConstant.h"
#include "shared_ptr.h"


const int MAX_DEPTH = 5;  // ���ݹ����


Camera::Camera(const Vec3f &viewPoint, const Vec3f &viewDirection, const Vec3f &headDirection, const float verticalFOV, const float distanceFromEye2Image, const unsigned imageWidth, const unsigned imageHeight)
    :_viewPoint(viewPoint)
{
    // ���������ĳ��ȱ������0
    if (viewDirection.norm() == 0 || headDirection.norm() == 0)
    {
        throw std::runtime_error("Norm of direction must not be equal to 0!");
    }

    // ��Ұ�Ǳ������0С��90
    if (verticalFOV <= 0 || verticalFOV >= 90)
    {
        throw std::runtime_error("FOV must not be under 0 or above 90!");
    }

    // �۾�������ľ���������0
    if (verticalFOV <= 0 || verticalFOV >= 90)
    {
        throw std::runtime_error("Distance from eye to image must not be under or equal to 0!");
    }

    // ͼ��ߴ�������0
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


// �������߸���
// ray: ����
// scene: ����
// depth: ���ݹ����
// ���ظù����ռ�������ɫ
Vec3f trace(const Ray &ray, const Scene &scene, const int depth)
{
    if(depth >= MAX_DEPTH)
    {
        return scene.backgroundColor();
    }

    float tNearest = INFINITY;  // �������1�������ļ���������ʱ��Ӧ�Ĺ���ʱ��
    const std::vector<const shared_ptr<Geometry> > geometries = scene.geometries();
    shared_ptr<Geometry> geometry(NULL);  // ���ߵ�1�������ļ�����

    Vec3f intersectionNormal(0.0, 0.0, 0.0);  // �������1�������ļ�����Ľ��㴦�ķ�����
    Vec3f intersectionNormalTemp(0.0, 0.0, 0.0);
    Vec3f intersectionColor(0.0, 0.0, 0.0);  // �������1�������ļ�����Ľ��㴦����ɫ
    Vec3f intersectionColorTemp(0.0, 0.0, 0.0);

    // �����1�������ļ�����
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

    // �����������û�������κμ����壬�򷵻س����ı�������ɫ
    if(!geometry)
    {
        return scene.backgroundColor();
    }

    intersectionNormal.normalize();

    Vec3f surfaceColor(0.0, 0.0, 0.0);  // �����ռ�������ɫ

    Vec3f intersectionPoint = ray.pointAt(tNearest);  // �������1�������ļ�����Ľ���

    float bias = 1e-4;  // ����һ���Դ���0��bias�����������Լ�Ͷ����Ӱ

    // �жϹ����Ƿ��ڼ������ڲ���������ڲ��򽫷�������ת��Ϊ���߷��䶨�ɵķ���
    bool inside = false;
    if(ray.direction().dot(intersectionNormal) > 0)
    {
        intersectionNormal *= -1;
        inside = true;
    }

    // ����ǹ�Դ TODO
    if (geometry->isLight())
    {
        return geometry->emissionColor();
    }

    // �������������
    float facingRatio = (-1) * ray.direction().dot(intersectionNormal);
    float mix = 0.1;
    float fresnelEffect = 1 * mix + pow(1.0 - facingRatio, 3) * (1 - mix);

    // ���㾵�淴�����
    Vec3f nextSpecular(0.0, 0.0, 0.0);
    if(geometry->specular() > 0)
    {
        Vec3f reflectDirection = ray.direction() - intersectionNormal * 2 * ray.direction().dot(intersectionNormal);
        reflectDirection.normalize();
        nextSpecular = trace(Ray(intersectionPoint + intersectionNormal * bias, reflectDirection), scene, depth + 1) * geometry->specular();
    }

    // �����������
    Vec3f nextRefraction(0.0, 0.0, 0.0);
    if(geometry->transparency() > 0)
    {
        float ior = 1.1;  // ������ TODO �˴������ʹ̶����������Ļ������������ΪGeometry�������֮һ
        float eta = inside ? ior : 1.0/ior;  // �����������ڼ������ڲ�����������תΪ����
        float cosin = (-1) * intersectionNormal.dot(ray.direction());
        float k = 1 - eta * eta * (1 - cosin * cosin);
        Vec3f refractionDirection = ray.direction() * eta + intersectionNormal * (eta * cosin - sqrt(k));
        refractionDirection.normalize();
        nextRefraction = trace(Ray(intersectionPoint - intersectionNormal * bias, refractionDirection), scene, depth + 1) * geometry->transparency();
    }

    // ������ɫ�Ƿ�����ߺ�������ߵĹ����ܺ�
    surfaceColor += (nextSpecular * fresnelEffect + nextRefraction * (1 - fresnelEffect));

    // ����������
    Vec3f diffuse(0.0, 0.0, 0.0);
    if(geometry->diffuse() > 0)
    {
        // ���㳡�������й�Դ�ڸ�������㹱�׵Ĺ�֮��
        for(unsigned i = 0; i < geometries.size(); i++)
        {
            if(geometries[i]->isLight())  // ����ǹ�Դ
            {
                // ��Դֻ����Sphere���͵�Geometry
                const Sphere *light = dynamic_cast<const Sphere *>(geometries[i].get());  // �˴���ԭʼָ������Ϊ���ʹ��shared_ptr�Ļ�����ὫSphere���������
                if (!light)
                {
                    throw std::runtime_error("Light must not be Geometry which is not Sphere!");
                }

                Vec3f transmission(1.0, 1.0, 1.0);
                Vec3f lightDirection = light->center() - intersectionPoint;
                lightDirection.normalize();

                // ���͹�Դ֮���Ƿ����ڵ����Դﵽ��ӰЧ��
                for(unsigned j = 0; j < geometries.size(); ++j)
                {
                    if(i != j)
                    {
                        if(geometries[j]->intersect(Ray(intersectionPoint + intersectionNormal * bias, lightDirection)) > 0)
                        {
                            // ���м���ͼ���ڵ����Ҹü���ͼ��͸���������͸���ȼ���͸��ϵ��
                            transmission = (transmission.array() * geometries[j]->surfaceColor().array()).matrix() * geometries[j]->transparency();  // ��Ϊ��������͸������ͼ�������������Դ˴�ֱ���ü���ͼ�εı�����ɫ����
                        }
                    }
                }                

                // �����Դ�ڽ��㴦�ı��棬��ù�Դ�ڴ˴�����Ϊ0
                surfaceColor += (transmission.array() * geometries[i]->emissionColor().array()).matrix() * std::max(float(0), intersectionNormal.dot(lightDirection)) * geometry->diffuse();
            }
        }

        // �������ڸ�������㹱�׵Ĺ� TODO
//         surfaceColor += scene.backgroundColor() * 0.2 * geometry->diffuse();
    }

    return (surfaceColor.array() * intersectionColor.array()).matrix() + geometry->emissionColor();
}


const cv::Mat & Camera::render(const Scene &scene)
{
    const float invWidth = 1 / float(_imageWidth), invHeight = 1 / float(_imageHeight);
    const float aspectRatio = _imageWidth / float(_imageHeight);
    const float imageRealHeightHalf = tan(PI * 0.5 * _verticalFOV / 180.0) * _distanceFromEye2Image;  // ͼ���ߵ�ʵ�ʳ���

    // ��ÿ�����ص���й��߸���
#pragma omp parallel for
    for(int row = 0; row < _imageHeight; row++)
    {
        for(int col = 0; col < _imageWidth; col++)
        {
            // ��ͼ�����ĵ�Ϊ����ԭ�㣬��Ϊx�ᣬ��Ϊy��ʱ�������ص��x��y����
            float x = (2 * ((col + 0.5) * invWidth) - 1) * imageRealHeightHalf * aspectRatio;
            float y = (1 - 2 * ((row + 0.5) * invHeight)) * imageRealHeightHalf;

            // ��������ص����ʵ��ά����
            Vec3f xx = _viewDirection.cross(_headDirection) * x;
            Vec3f yy = _headDirection * y;
            Vec3f pixelCoordinate = _viewPoint + _viewDirection * _distanceFromEye2Image + xx + yy;  // �����ص����ʵ��ά����

            Vec3f pixel = trace(Ray(_viewPoint, pixelCoordinate - _viewPoint), scene, 0);
            for (unsigned i = 0; i < 3; i++)
            {
                _image.at<cv::Vec3b>(row, col)[i] = (unsigned char)(std::min(float(1), pixel[2 - i]) * 255);
            }
        }
    }

    return _image;
}
