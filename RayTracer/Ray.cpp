#include "Ray.h"


Ray::Ray(const Vec3f &origin, const Vec3f &direction)
    :_origin(origin)
    ,_direction(direction * (1.0 / direction.length()))
{
}
