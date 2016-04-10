#include "Triangle.h"
#include <stdexcept>


const Vec3f __defaultVertices[3] = {Vec3f(-1.0, 0.0, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 1.732, 0.0)};
const std::vector<Vec3f> Triangle::_defaultVertices(__defaultVertices, __defaultVertices + 3);


Triangle::Triangle(const std::vector<Vec3f> &vertices, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :Geometry(surfaceColor, emissionColor, transparency, reflection)
    ,_vertices(vertices)
{
    // 顶点数量必须为3
    if (vertices.size() != 3)
    {
        throw std::runtime_error("Number of Triangle's vertices must not be any value but 3!");
    }

    // 计算两条边和单位法向量
    _edge1 = _vertices[0] - _vertices[1];
    _edge2 = _vertices[0] - _vertices[2];
    _normal = (_edge1.cross(_edge2)).normalize();
}


float Triangle::intersect(const Ray &ray, Vec3f &normal) const
{
    Vec3f s = _vertices[0] - ray.origin();
    float inv = (float)1 / Vec3f::det(ray.direction(), _edge1, _edge2);
    float t = Vec3f::det(s, _edge1, _edge2) * inv;
    float beta = Vec3f::det(ray.direction(), s, _edge2) * inv;
    float gamma = Vec3f::det(ray.direction(), _edge1, s) * inv;
    if (t > 0 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && beta + gamma <= 1)
    {
        normal = _normal;
        return t;
    }
    else
    {
        return -1;
    }
}
