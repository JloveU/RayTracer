#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <vector>
#include <stdexcept>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "shared_ptr.h"


// 三角形
class Triangle : public Geometry
{

public:
    Triangle(const Vec3f &vertex0 = _defaultVertices[0], const Vec3f &vertex1 = _defaultVertices[1], const Vec3f &vertex2 = _defaultVertices[2], const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const Vec3f & vertice0() const
    {
        return _vertices[0];
    }

    inline const Vec3f & vertice1() const
    {
        return _vertices[1];
    }

    inline const Vec3f & vertice2() const
    {
        return _vertices[2];
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    void setTextureCoordinates(const Vec2f &textureCoordinate0, const Vec2f &textureCoordinate1, const Vec2f &textureCoordinate2);

    virtual void transform(const Mat4f &t);

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

private:
    // 根据三个顶点更新计算其他成员变量
    void updateCache();

private:
    Vec3f _vertices[3];  // 三角形的3个顶点（按逆时针方向确定正面）
    Vec3f _edge1, _edge2;  // 分别为三角形的两条边，用于计算与光线的交点
    Vec3f _normal;  // 单位法向量
    std::vector<Vec2f> _textureCoordinates;  // 三角形的3个顶点的纹理坐标

public:
    // 各属性的默认值
    static const Vec3f _defaultVertices[3];

};


#endif
