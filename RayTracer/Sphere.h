#ifndef SPHERE_H
#define SPHERE_H


#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"


// 球体
class Sphere : public Geometry
{

public:
    Sphere(const Vec3f &center = _defaultCenter, const float radius = _defaultRadius, const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

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

    virtual void transform(const Mat4f &t);

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

private:
    Vec3f _center;
    float _radius;
    float _radius2;  // 半径的平方

public:
    // 各属性的默认值
    static const Vec3f _defaultCenter;
    static const float _defaultRadius;

};


#endif
