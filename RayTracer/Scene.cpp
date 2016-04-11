#include "Scene.h"
#include <stdexcept>
#include "Triangle.h"
#include "Polygon.h"
#include "MathConstant.h"


const Vec3f Scene::_defaultBackgroundColor = Vec3f(1.0, 1.0, 1.0);


Scene::Scene(const Vec3f &backgroundColor)
    :_geometries()
{
    // ��ɫֵ������ڵ���0
    if (backgroundColor.x < 0 || backgroundColor.y < 0 || backgroundColor.z < 0)
    {
        throw std::runtime_error("Value of color must not be under 0!");
    }

    _backgroundColor = backgroundColor;
}


void Scene::addGeometry(Geometry *geometry)
{
    _geometries.push_back(geometry);
}


void Scene::removeAllGeometries()
{
    // ���ͷ��ڴ�
    for (unsigned i = 0; i < _geometries.size(); i++)
    {
        delete _geometries[i];
    }

    _geometries.clear();
}


void Scene::addAxes()
{
    float axesSize = 1.0;

    // ������ԭ�㴦��3���ֱ�ƽ����xy��yz��zxƽ���������
    addGeometry(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(axesSize, 0.0, 0.0), Vec3f(0.0, axesSize, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
    addGeometry(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, axesSize, 0.0), Vec3f(0.0, 0.0, axesSize), Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
    addGeometry(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, 0.0, axesSize), Vec3f(axesSize, 0.0, 0.0), Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));

    // ��3��������ֱ��һ�����Σ����γ��������޴󣬿��������С��
    addGeometry(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(INFINITY, 0.0, 0.0), Vec3f(0.0, 0.02, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
    addGeometry(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, INFINITY, 0.0), Vec3f(0.0, 0.0, 0.02), Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
    addGeometry(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, 0.0, INFINITY), Vec3f(0.02, 0.0, 0.0), Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
}
