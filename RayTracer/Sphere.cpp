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
    Vec3f vectorRayOrigin2SphereCenter = _center - ray.origin();  //�ӹ���ԭ�㵽���ĵ�����

    if (vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) > _radius2)  // ����ԭ��������
    {
        float projectionLength = vectorRayOrigin2SphereCenter.dot(ray.direction());  // ���߹���ԭ��ָ�����ĵ������ڹ����ϵ�ͶӰ
        float distance2 = vectorRayOrigin2SphereCenter.dot(vectorRayOrigin2SphereCenter) - projectionLength * projectionLength;  // ���ĵ����ߵľ���
        if (distance2 < _radius2)  // ��2������
        {
            float chordLengthHalf = sqrt(_radius2 - distance2);  // �ཻ�Ұ볤��
            float t = projectionLength - chordLengthHalf;
            normal = (ray.pointAt(t) - _center).normalize();
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
        normal = (ray.pointAt(t) - _center).normalize();
        return t;
    }
}