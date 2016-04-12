#ifndef GEOMETRYUNION_H
#define GEOMETRYUNION_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// 由多个（可以是不同类型的）几何图形组合成的新的几何图形，子几何图形的父类基本属性（颜色等）失效
class GeometryUnion : public Geometry
{

public:
    GeometryUnion(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float reflection = _defaultReflection);

    inline const std::vector<Geometry *> & geometries() const
    {
        return _geometries;
    }

    // 添加几何图形
    void addGeometry(Geometry *geometry);

    // 删除所有几何图形
    void removeAllGeometries();

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const;

protected:
    std::vector<Geometry *> _geometries;

};


#endif
