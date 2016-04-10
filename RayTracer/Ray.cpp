#include "Ray.h"


const Vec3f Ray::_defaultOrigin = Vec3f(0.0, 0.0, 0.0);
const Vec3f Ray::_defaultDirection = Vec3f(0.0, 0.0, -1.0);


Ray::Ray(const Vec3f &origin, const Vec3f &direction)
    :_origin(origin)
    ,_direction(direction * (1.0 / direction.length()))
{
}
