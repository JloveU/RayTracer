#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// 三角形
class Triangle : public Geometry
{

public:
    Triangle(const Vec3f &vertex0 = _defaultVertices[0], const Vec3f &vertex1 = _defaultVertices[1], const Vec3f &vertex2 = _defaultVertices[2], const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float reflection = _defaultReflection);

    inline const Vec3f * vertices() const
    {
        return _vertices;
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const;

private:
    Vec3f _vertices[3];  // 三角形的3个顶点（按逆时针方向确定正面）
    Vec3f _edge1, _edge2;  // 分别为三角形的两条边，用于计算与光线的交点
    Vec3f _normal;  // 单位法向量

public:
    // 各属性的默认值
    static const Vec3f _defaultVertices[3];

};


#endif
