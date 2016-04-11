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
    // ���ͷ��ڴ�
    for (unsigned i = 0; i < _geometries.size(); i++)
    {
        delete _geometries[i];
    }

    _geometries.clear();
}


float GeometryUnion::intersect(const Ray &ray, Vec3f &normal) const
{
    // �ֱ����ÿһ���Ӽ���ͼ������ߵĽ��㣬ȡ�������һ��
    float tNearest, tTemp;
    Vec3f normalNearest, normalTemp;

    // ���Ӽ���ͼ�����˳���ҵ�1��������ཻ���Ӽ���ͼ��
    unsigned index, nearestIndex = 0;
    for (index = 0; index < _geometries.size(); index++)
    {
        tNearest = _geometries[index]->intersect(ray, normalNearest);
        if (tNearest > 0)
        {
            break;
        }
    }
    if (tNearest <= 0)  // ��������Ӽ���ͼ�ζ���������ཻ�������ϼ���ͼ�β�������ཻ
    {
        return -1;
    }

    // ��ʣ�µ��Ӽ���ͼ����Ѱ�ҽ����������һ��
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
