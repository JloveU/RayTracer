#ifndef POLYGON_H
#define POLYGON_H


#include <vector>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "Plane.h"


// 多边形
class Polygon : public Geometry
{

public:
    Polygon(const std::vector<Vec3f> &vertices = _defaultVertices, const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const std::vector<Vec3f> & vertices() const
    {
        return _vertices;
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

private:
    std::vector<Vec3f> _vertices;  // 所有顶点（按逆时针方向确定正面）
    Vec3f _normal;  // 单位法向量
    Plane _plane;  // 该多边形所在平面

public:
    // 各属性的默认值
    static const std::vector<Vec3f> _defaultVertices;

};


#endif
