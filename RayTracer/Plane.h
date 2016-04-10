#ifndef PLANE_H
#define PLANE_H


#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// 平面
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
    Vec3f _point;  // 平面的显示方程中的点
    Vec3f _normal;  // 单位法向量
    float _d;  // 平面的隐式方程的常数项

};


#endif
