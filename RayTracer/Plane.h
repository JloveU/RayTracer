#ifndef PLANE_H
#define PLANE_H


#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// ƽ��
class Plane : public Geometry
{

public:
    Plane(const Vec3f &point=Vec3f(0.0, 0.0, 0.0), const Vec3f &normal=Vec3f(0.0, 1.0, 0.0), const Vec3f &surfaceColor=Vec3f(1.0, 1.0, 1.0), const Vec3f &emissionColor = Vec3f(0.0, 0.0, 0.0), const float transparency = 0.0, const float reflection = 0.0);

    inline const Vec3f & point() const
    {
        return _point;
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const;

private:
    Vec3f _point;  // ƽ�����ʾ�����еĵ�
    Vec3f _normal;  // ��λ������
    float _d;  // ƽ�����ʽ���̵ĳ�����

};


#endif
