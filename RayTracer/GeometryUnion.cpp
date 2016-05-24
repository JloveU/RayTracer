#include "GeometryUnion.h"


GeometryUnion::GeometryUnion(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
    :Geometry(surfaceColor, emissionColor, transparency, specular, diffuse)
{
}


void GeometryUnion::addGeometry(const shared_ptr<Geometry> &geometry)
{
    _geometries.push_back(geometry);
}


void GeometryUnion::removeAllGeometries()
{
    _geometries.clear();
}


float GeometryUnion::intersect(const Ray &ray, Vec3f &normal, Vec3f &color) const
{
    // �ֱ����ÿһ���Ӽ���ͼ������ߵĽ��㣬ȡ�������һ��
    float tNearest = -1, tTemp;
    Vec3f normalNearest, normalTemp;
    Vec3f colorNearest, colorTemp;

    // ���Ӽ���ͼ�����˳���ҵ�1��������ཻ���Ӽ���ͼ��
    unsigned index, nearestIndex = 0;
    for (index = 0; index < _geometries.size(); index++)
    {
        tNearest = _geometries[index]->intersect(ray, normalNearest, colorNearest);
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
        tTemp = _geometries[index]->intersect(ray, normalTemp, colorTemp);
        if (tTemp > 0 && tTemp < tNearest)
        {
            tNearest = tTemp;
            normalNearest = normalTemp;
            colorNearest = colorTemp;
        }
    }

    normal = normalNearest;
    color = colorNearest;
    return tNearest;
}
