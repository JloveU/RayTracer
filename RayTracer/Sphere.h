#ifndef SPHERE_H
#define SPHERE_H


#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// 球体
class Sphere : public Geometry
{

public:
    Sphere(const Vec3f &center=Vec3f(0.0, 0.0, 0.0), const float radius=1, const Vec3f &surfaceColor=Vec3f(1.0, 1.0, 1.0), const Vec3f &emissionColor = Vec3f(0.0, 0.0, 0.0), const float transparency = 0.0, const float reflection = 0.0);

    inline const Vec3f & center() const
    {
        return _center;
    }

    inline float radius() const
    {
        return _radius;
    }

    inline float radius2() const
    {
        return _radius2;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const;

private:
    Vec3f _center;
    float _radius;
    float _radius2;  // 半径的平方

};


#endif
