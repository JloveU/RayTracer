#include "GeometryUnion.h"


GeometryUnion::GeometryUnion(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :Geometry(surfaceColor, emissionColor, transparency, reflection)
{
}


void GeometryUnion::addGeometry(Geometry *geometry)
{
    _geometries.push_back(geometry);
}


void GeometryUnion::removeAllGeometries()
{
    // 先释放内存
    for (unsigned i = 0; i < _geometries.size(); i++)
    {
        delete _geometries[i];
    }

    _geometries.clear();
}


float GeometryUnion::intersect(const Ray &ray, Vec3f &normal) const
{
    // 分别计算每一个子几何图形与光线的交点，取最近的那一个
    float tNearest, tTemp;
    Vec3f normalNearest, normalTemp;

    // 按子几何图形添加顺序找到1个与光线相交的子几何图形
    unsigned index, nearestIndex = 0;
    for (index = 0; index < _geometries.size(); index++)
    {
        tNearest = _geometries[index]->intersect(ray, normalNearest);
        if (tNearest > 0)
        {
            break;
        }
    }
    if (tNearest <= 0)  // 如果所有子几何图形都不与光线相交，则该组合几何图形不与光线相交
    {
        return -1;
    }

    // 在剩下的子几何图形中寻找交点最近的那一个
    for (index++; index < _geometries.size(); index++)
    {
        tTemp = _geometries[index]->intersect(ray, normalTemp);
        if (tTemp > 0 && tTemp < tNearest)
        {
            tNearest = tTemp;
            normalNearest = normalTemp;
        }
    }

    normal = normalNearest;
    return tNearest;
}
