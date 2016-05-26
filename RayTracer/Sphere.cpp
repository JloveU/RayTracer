#include "Sphere.h"
#include <stdexcept>
#include <math.h>


const Vec3f Sphere::_defaultCenter = Vec3f(0.0, 0.0, 0.0);
const float Sphere::_defaultRadius = 1.0;


Sphere::Sphere(const Vec3f &center, const float radius, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
    :Geometry(surfaceColor, emissionColor, transparency, specular, diffuse)
    ,_center(center)
    ,_radius(radius)
    ,_radius2(radius * radius)
{
    // �뾶�������0
    if (radius <= 0)
    {
        throw std::runtime_error("Radius of Sphere must not be under or equal to 0!");
    }

    _radius = radius;
    _radius2 = radius * radius;
}


void Sphere::transform(const Mat4f &t)
{
    Matrix::transform(_center, t);
}


float Sphere::intersect(const Ray &ray, Vec3f &normal, Vec3f &color) const
{
    // �ü��η��������������Ľ���
    Vec3f vectorRayOrigin2SphereCenter = _center - ray.origin();  //�ӹ���ԭ�㵽���ĵ�����

    if (vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) > _radius2)  // ����ԭ��������
    {
        float projectionLength = vectorRayOrigin2SphereCenter.dot(ray.direction());  // ���߹���ԭ��ָ�����ĵ������ڹ����ϵ�ͶӰ
        float distance2 = vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) - projectionLength * projectionLength;  // ���ĵ����ߵľ���
        if (distance2 < _radius2)  // ��2������
        {
            float chordLengthHalf = sqrt(_radius2 - distance2);  // �ཻ�Ұ볤��
            float t = projectionLength - chordLengthHalf;
            normal = ray.pointAt(t) - _center;
            normal.normalize();
            color = surfaceColor();  // TODO ��������
            return t;
        } 
        else  // �޽���
        {
            return -1;
        }
    }
    else  // ����ԭ�������ڣ���1�����㣩
    {
        float projectionLength = vectorRayOrigin2SphereCenter.dot(ray.direction());  // ���߹���ԭ��ָ�����ĵ������ڹ����ϵ�ͶӰ
        float distance2 = vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) - projectionLength * projectionLength;  // ���ĵ����ߵľ���
        float chordLengthHalf = sqrt(_radius2 - distance2);  // �ཻ�Ұ볤��
        float t = projectionLength + chordLengthHalf;
        normal = ray.pointAt(t) - _center;
        normal.normalize();
        color = surfaceColor();  // TODO ��������
        return t;
    }
}
