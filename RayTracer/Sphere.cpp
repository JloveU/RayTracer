#include "Sphere.h"
#include <math.h>


Sphere::Sphere(const Vec3f &center, const float radius, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :Geometry(surfaceColor, emissionColor, transparency, reflection)
    ,_center(center)
    ,_radius(radius)
    ,_radius2(radius * radius)
{
}


float Sphere::intersect(const Ray &ray, Vec3f &normal) const
{
    Vec3f vectorRayOrigin2SphereCenter = _center - ray.origin();  //从光线原点到球心的向量

    if (vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) > _radius2)  // 光线原点在球外
    {
        float projectionLength = vectorRayOrigin2SphereCenter.dot(ray.direction());  // 光线光线原点指向球心的向量在光线上的投影
        float distance2 = vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) - projectionLength * projectionLength;  // 球心到光线的距离
        if (distance2 < _radius2)  // 有2个交点
        {
            float chordLengthHalf = sqrt(_radius2 - distance2);  // 相交弦半长度
            float t = projectionLength - chordLengthHalf;
            normal = (ray.pointAt(t) - _center).normalize();
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
        normal = (ray.pointAt(t) - _center).normalize();
        return t;
    }
}
