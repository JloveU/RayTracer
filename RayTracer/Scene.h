#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"


// 场景
class Scene
{

public:
    Scene(const Vec3f &backgroundColor=Vec3f(1.0, 1.0, 1.0));

    inline const Vec3f & backgroundColor() const
    {
        return _backgroundColor;
    }

    inline const std::vector<Geometry *> & geometries() const
    {
        return _geometries;
    }

    // 添加几何图形到场景中
    void addGeometry(Geometry *geometry);

    // 删除场景中的所有几何图形
    void removeAllGeometries();

private:
    Vec3f _backgroundColor;
    std::vector<Geometry *> _geometries;

};


#endif
