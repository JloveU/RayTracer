#include "Matrix.h"
#include <math.h>


float Matrix::det(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3)
{
    return v1.x() * (v2.y()*v3.z()-v2.z()*v3.y()) - v1.y() * (v2.x()*v3.z()-v2.z()*v3.x()) + v1.z() * (v2.x()*v3.y()-v2.y()*v3.x());
}


Mat4f Matrix::formRotateMatrix(const Vec3f &axis, const float angle)
{
    Vec3f axisNormalized = axis.normalized();
    float x = axisNormalized.x();
    float y = axisNormalized.y();
    float z = axisNormalized.z();
    float c = cos(angle);
    float s = sin(angle);

    Mat4f rotateMatrix;
    rotateMatrix << 
        c + (1 - c) * x * x,     (1 - c) * y * x + s * z, (1 - c) * z * x - s * y, 0,
        (1 - c) * x * y - s * z, c + (1 - c) * y * y,     (1 - c) * z * y + s * x, 0,
        (1 - c) * x * z + s * y, (1 - c) * y * z - s * x, c + (1 - c) * z * z,     0,
        0,                       0,                       0,                       1;

    return rotateMatrix;
}

void Matrix::transform(Vec3f &vector, const Mat4f &t)
{
    Vec4f vectorAugmented(vector.x(), vector.y(), vector.z(), 1);
    Vec4f vectorAugmentedTransformed = t * vectorAugmented;
    for (unsigned i = 0; i < 3; i++)
    {
        vector[i] = vectorAugmentedTransformed[i] / vectorAugmentedTransformed[3];
    }
}
