#include "Box.h"
#include <iostream>
#include <stdexcept>


const Vec3f Box::_defaultOrigin = Vec3f(0.0, 0.0, 0.0);
const Vec3f Box::_defaultSize = Vec3f(1.0, 1.0, 1.0);


Box::Box(const Vec3f &origin, const Vec3f &size, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
    :Geometry(surfaceColor, emissionColor, transparency, specular, diffuse)
    ,_origin(origin)
{
    // 尺寸必须大于0
    if (size.x() <= 0 || size.y() <= 0 || size.z() <= 0)
    {
        throw std::runtime_error("Size must not be under or equal to 0!");
    }

    _size = size;

    // 计算各Slab，TODO 此处还未考虑长方体旋转问题
    Vec3f normals[3];
    normals[0] = Vec3f(1.0, 0.0, 0.0);
    normals[1] = Vec3f(0.0, 1.0, 0.0);
    normals[2] = Vec3f(0.0, 0.0, 1.0);
    for (unsigned i = 0; i < 3; i++)
    {
        _slabs[i][0] = Plane(_origin, normals[i]);
        Vec3f pointOnFartherPlane = _origin;
        pointOnFartherPlane[i] += _size[i];
        _slabs[i][1] = Plane(pointOnFartherPlane, normals[i]);
    }
}


float Box::intersect(const Ray &ray, Vec3f &normal, Vec3f &color) const
{
    // 用基于Slab的长方体求交算法计算长方体与光线的交点
    // 分别计算3个slab与光线的交点
    float tMin[3], tMax[3];
    Vec3f normals[3];
    for (unsigned i = 0; i < 3; i++)
    {
        float t0 = _slabs[i][0].intersect(ray, normals[i]);
        float t1 = _slabs[i][1].intersect(ray, normals[i]);
        tMin[i] = std::min(t0, t1);
        tMax[i] = std::max(t0, t1);
    }

    // 找到最近点和最远点
    int nearestSlabIndex = 0;
    float tMinMax = tMin[0];
    for (unsigned i = 1; i < 3; i++)
    {
        if (tMin[i] > tMinMax)
        {
            tMinMax = tMin[i];
            nearestSlabIndex = i;
        }
    }
    float tMaxMin = tMax[0];
    for (unsigned i = 1; i < 3; i++)
    {
        if (tMax[i] < tMaxMin)
        {
            tMaxMin = tMax[i];
        }
    }

    if (tMinMax < tMaxMin)  // 如果最近点比最远点近，则长方体与光线有交点
    {
        normal = normals[nearestSlabIndex];
        color = surfaceColor();  // TODO 处理纹理
        return tMinMax;
    }
    else
    {
        return -1;
    }
}
