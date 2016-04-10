#include "Plane.h"


const Vec3f Plane::_defaultPoint = Vec3f(0.0, 0.0, 0.0);
const Vec3f Plane::_defaultNormal = Vec3f(0.0, 1.0, 0.0);


Plane::Plane(const Vec3f &point, const Vec3f &normal, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :Geometry(surfaceColor, emissionColor, transparency, reflection)
    ,_point(point)
    ,_normal(normal * (1.0 / normal.length()))
    ,_d((-1) * _normal.dot(_point))
{
}


float Plane::intersect(const Ray &ray, Vec3f &normal) const
{
    float t = (-1) * (_d + _normal.dot(ray.origin())) / (_normal.dot(ray.direction()));
    if (t > 0)
    {
        normal = _normal;
        return t;
    }
    else
    {
        return -1;
    }
}
