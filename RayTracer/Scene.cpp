#include "Scene.h"
#include <stdexcept>


const Vec3f Scene::_defaultBackgroundColor = Vec3f(1.0, 1.0, 1.0);


Scene::Scene(const Vec3f &backgroundColor)
    :_geometries()
{
    // 颜色值必须大于等于0
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
    // 先释放内存
    for (unsigned i = 0; i < _geometries.size(); i++)
    {
        delete _geometries[i];
    }

    _geometries.clear();
}
