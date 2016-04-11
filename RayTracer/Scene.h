#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"


// 场景
class Scene
{

public:
    Scene(const Vec3f &backgroundColor = _defaultBackgroundColor);

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

    // 添加坐标系标志到场景中
    void addAxes();

private:
    Vec3f _backgroundColor;
    std::vector<Geometry *> _geometries;

public:
    // 各属性的默认值
    static const Vec3f _defaultBackgroundColor;

};


#endif
