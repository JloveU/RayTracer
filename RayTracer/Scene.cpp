#include "Scene.h"
#include <stdexcept>
#include "Triangle.h"
#include "Polygon.h"
#include "MathConstant.h"


const Vec3f Scene::_defaultBackgroundColor = Vec3f(1.0, 1.0, 1.0);


Scene::Scene(const Vec3f &backgroundColor)
    :_geometries()
{
    // 颜色值必须大于等于0
    if (backgroundColor.x() < 0 || backgroundColor.y() < 0 || backgroundColor.z() < 0)
    {
        throw std::runtime_error("Value of color must not be under 0!");
    }

    _backgroundColor = backgroundColor;
}


void Scene::addGeometry(const shared_ptr<Geometry> &geometry)
{
    _geometries.push_back(geometry);
}


void Scene::removeAllGeometries()
{
    _geometries.clear();
}


void Scene::addAxes()
{
    float axesSize = 1.0;

    // 在坐标原点处放3个分别平行于xy、yz、zx平面的三角形
    addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(axesSize, 0.0, 0.0), Vec3f(0.0, axesSize, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0)));
    addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, axesSize, 0.0), Vec3f(0.0, 0.0, axesSize), Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0)));
    addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, 0.0, axesSize), Vec3f(axesSize, 0.0, 0.0), Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0)));

    // 沿3个坐标轴分别放一个矩形（矩形长近似无限大，宽近似无限小）
    addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(INFINITY, 0.0, 0.0), Vec3f(0.0, 0.02, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0)));
    addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, INFINITY, 0.0), Vec3f(0.0, 0.0, 0.02), Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0)));
    addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, 0.0, INFINITY), Vec3f(0.02, 0.0, 0.0), Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0)));
}
