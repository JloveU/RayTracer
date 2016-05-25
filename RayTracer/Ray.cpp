#include "Ray.h"
#include <stdexcept>


const Vec3f Ray::_defaultOrigin = Vec3f(0.0, 0.0, 0.0);
const Vec3f Ray::_defaultDirection = Vec3f(0.0, 0.0, -1.0);


Ray::Ray(const Vec3f &origin, const Vec3f &direction)
    :_origin(origin)
{
    // 方向向量的长度必须大于0
    if (direction.norm() == 0)
    {
        throw std::runtime_error("Norm of direction must not be equal to 0!");
    }

    _direction = direction;
    _direction.normalize();
}
