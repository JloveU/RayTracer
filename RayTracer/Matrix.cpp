#include "Matrix.h"


float det(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3)
{
    return v1.x() * (v2.y()*v3.z()-v2.z()*v3.y()) - v1.y() * (v2.x()*v3.z()-v2.z()*v3.x()) + v1.z() * (v2.x()*v3.y()-v2.y()*v3.x());
}
