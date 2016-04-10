#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// ������
class Triangle : public Geometry
{

public:
    Triangle(const std::vector<Vec3f> &vertices = _defaultVertices, const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float reflection = _defaultReflection);

    inline const std::vector<Vec3f> & vertices() const
    {
        return _vertices;
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const;

private:
    std::vector<Vec3f> _vertices;  // �����ε�3�����㣨����ʱ�뷽��ȷ�����棩
    Vec3f _edge1, _edge2;  // �ֱ�Ϊ�����ε������ߣ����ڼ�������ߵĽ���
    Vec3f _normal;  // ��λ������

public:
    // �����Ե�Ĭ��ֵ
    static const std::vector<Vec3f> _defaultVertices;

};


#endif
