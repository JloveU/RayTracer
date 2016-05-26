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
    // 半径必须大于0
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
    // 用几何方法求光线与球体的交点
    Vec3f vectorRayOrigin2SphereCenter = _center - ray.origin();  //从光线原点到球心的向量

    if (vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) > _radius2)  // 光线原点在球外
    {
        float projectionLength = vectorRayOrigin2SphereCenter.dot(ray.direction());  // 光线光线原点指向球心的向量在光线上的投影
        float distance2 = vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) - projectionLength * projectionLength;  // 球心到光线的距离
        if (distance2 < _radius2)  // 有2个交点
        {
            float chordLengthHalf = sqrt(_radius2 - distance2);  // 相交弦半长度
            float t = projectionLength - chordLengthHalf;
            normal = ray.pointAt(t) - _center;
            normal.normalize();
            color = surfaceColor();  // TODO 处理纹理
            return t;
        } 
        else  // 无交点
        {
            return -1;
        }
    }
    else  // 光线原点在球内（有1个交点）
    {
        float projectionLength = vectorRayOrigin2SphereCenter.dot(ray.direction());  // 光线光线原点指向球心的向量在光线上的投影
        float distance2 = vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) - projectionLength * projectionLength;  // 球心到光线的距离
        float chordLengthHalf = sqrt(_radius2 - distance2);  // 相交弦半长度
        float t = projectionLength + chordLengthHalf;
        normal = ray.pointAt(t) - _center;
        normal.normalize();
        color = surfaceColor();  // TODO 处理纹理
        return t;
    }
}
