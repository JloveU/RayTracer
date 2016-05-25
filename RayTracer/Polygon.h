#ifndef POLYGON_H
#define POLYGON_H


#include <vector>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "Plane.h"


// �����
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
    std::vector<Vec3f> _vertices;  // ���ж��㣨����ʱ�뷽��ȷ�����棩
    Vec3f _normal;  // ��λ������
    Plane _plane;  // �ö��������ƽ��

public:
    // �����Ե�Ĭ��ֵ
    static const std::vector<Vec3f> _defaultVertices;

};


#endif
