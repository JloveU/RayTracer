#ifndef BOX_H
#define BOX_H


#include <vector>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "Plane.h"


// 长方体
class Box : public Geometry
{

public:
    Box(const Vec3f &origin = _defaultOrigin, const Vec3f &size = _defaultSize, const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const Vec3f & origin() const
    {
        return _origin;
    }

    inline const Vec3f & size() const
    {
        return _size;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

private:
    Vec3f _origin;  // 原点（最靠近坐标原点的顶点）
    Vec3f _size;  // 尺寸（分别与x、y、z轴平行的边的边长）
    Plane _slabs[3][2];  // 3个平面对(Slab)，依次分别对应初始未旋转状态时的yz、zx、xy平面

public:
    // 各属性的默认值
    static const Vec3f _defaultOrigin;
    static const Vec3f _defaultSize;

};


#endif
