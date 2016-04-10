#include "Scene.h"


Scene::Scene(const Vec3f &backgroundColor)
    :_backgroundColor(backgroundColor)
    ,_geometries()
{
}


void Scene::addGeometry(Geometry *geometry)
{
    _geometries.push_back(geometry);
}


void Scene::removeAllGeometries()
{
    // œ» Õ∑≈ƒ⁄¥Ê
    for (unsigned i = 0; i < _geometries.size(); i++)
    {
        delete _geometries[i];
    }

    _geometries.clear();
}
