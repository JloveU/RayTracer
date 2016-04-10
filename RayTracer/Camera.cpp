#include "Camera.h"
#include <iostream>
#include "Sphere.h"


const float PI = 3.141592653589;  // Բ����
const float INFINITY = 1e8;  // �����ֵ
const int MAX_DEPTH = 5;  // ���ݹ����


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


// �������߸���
// ray: ����
// scene: ����
// depth: ���ݹ����
// ���ظù����ռ�������ɫ
Vec3f trace(const Ray &ray, const Scene &scene, const int depth)
{
    float tNearest = INFINITY;  // �������1�������ļ���������ʱ��Ӧ�Ĺ���ʱ��
    const std::vector<Geometry *> geometries = scene.geometries();
    const Geometry *geometry = NULL;  // ���ߵ�1�������ļ�����

    Vec3f intersectionNormal(0.0, 0.0, 0.0);  // �������1�������ļ�����Ľ��㴦�ķ�����
    Vec3f intersectionNormalTemp(0.0, 0.0, 0.0);

    // �����1�������ļ�����
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

    // ���ٷ�����������
    if((geometry->transparency() > 0 || geometry->reflection() > 0) && depth < MAX_DEPTH)
    {
        // �������������
        float facingRatio = (-1) * ray.direction().dot(intersectionNormal);
        float mix = 0.1;
        float fresnelEffect = 1 * mix + pow(1.0 - facingRatio, 3) * (1 - mix);

        // �������
        Vec3f reflectDirection = ray.direction() - intersectionNormal * 2 * ray.direction().dot(intersectionNormal);
        reflectDirection.normalize();
        Vec3f nextReflection = trace(Ray(intersectionPoint + intersectionNormal * bias, reflectDirection), scene, depth + 1);

        // �������
        Vec3f nextRefraction = 0;
        if(geometry->transparency())  // ֻ�иü�������͸����ʱ�򣬲Ŵ���������߲�����֮
        {
            float ior = 1.1;  // ������ TODO �˴������ʹ̶����������Ļ������������ΪGeometry�������֮һ
            float eta = inside ? ior : 1.0/ior;  // �����������ڼ������ڲ�����������תΪ����
            float cosin = (-1) * intersectionNormal.dot(ray.direction());
            float k = 1 - eta * eta * (1 - cosin * cosin);
            Vec3f refractionDirection = ray.direction() * eta + intersectionNormal * (eta * cosin - sqrt(k));
            refractionDirection.normalize();
            nextRefraction = trace(Ray(intersectionPoint - intersectionNormal * bias, refractionDirection), scene, depth + 1);
        }

        // ������ɫ�Ƿ�����ߺ�������ߵĹ����ܺ�
        surfaceColor = (nextReflection * fresnelEffect + nextRefraction * (1 - fresnelEffect) * geometry->transparency()) * geometry->surfaceColor();
    }
    else  // ����ü������������������ʻ��ǹ�Դ������Ҫ�������ٹ���
    {

        if (false)  //geometry->emissionColor().x > 0)  // ����ǹ�Դ TODO
        {
            surfaceColor = geometry->emissionColor();
        } 
        else  // ����Ǳ�������������ʵļ�����
        {
            // ���㳡�������й�Դ�ڸ�������㹱�׵Ĺ�֮��
            for(unsigned i = 0; i < geometries.size(); i++)
            {
                if(geometries[i]->emissionColor().x > 0)  // ����ǹ�Դ
                {
                    // ��Դֻ����Sphere���͵�Geometry
                    const Sphere *light = dynamic_cast<const Sphere *>(geometries[i]);
                    if (!light)
                    {
                        throw std::runtime_error("Light must not be Geometry which is not Sphere!");
                    }

                    float transmission = 1.0;
                    Vec3f lightDirection = light->center() - intersectionPoint;
                    lightDirection.normalize();

                    // ���͹�Դ֮���Ƿ����ڵ����Դﵽ��ӰЧ��
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

                    // �����Դ�ڽ��㴦�ı��棬��ù�Դ�ڴ˴�����Ϊ0
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
    float imageRealHeightHalf = tan(PI * 0.5 * _verticalFOV / 180.0) * _distanceFromEye2Image;  // ͼ���ߵ�ʵ�ʳ���

    // ��ÿ�����ص���й��߸���
    for(unsigned row = 0; row < _imageHeight; row++)
    {
        for(unsigned col = 0; col < _imageWidth; col++)
        {
            // ��ͼ�����ĵ�Ϊ����ԭ�㣬��Ϊx�ᣬ��Ϊy��ʱ�������ص��x��y����
            float x = (2 * ((col + 0.5) * invWidth) - 1) * imageRealHeightHalf * aspectRatio;
            float y = (1 - 2 * ((row + 0.5) * invHeight)) * imageRealHeightHalf;

            // ��������ص����ʵ��ά����
            Vec3f xx = _viewDirection.cross(_headDirection) * x;
            Vec3f yy = _headDirection * y;
            Vec3f pixelCoordinate = _viewPoint + _viewDirection * _distanceFromEye2Image + xx + yy;  // �����ص����ʵ��ά����

            Vec3f pixel = trace(Ray(_viewPoint, pixelCoordinate - _viewPoint), scene, 0);
            _image.at<cv::Vec3b>(row, col)[0] = (unsigned char)(std::min(float(1), pixel.z) * 255);
            _image.at<cv::Vec3b>(row, col)[1] = (unsigned char)(std::min(float(1), pixel.y) * 255);
            _image.at<cv::Vec3b>(row, col)[2] = (unsigned char)(std::min(float(1), pixel.x) * 255);
        }
    }

    return _image;
}
