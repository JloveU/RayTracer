#ifndef PLANE_H
#define PLANE_H


#include <math.h>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "MathConstant.h"


// ƽ��
class Plane : public Geometry
{

public:
    Plane(const Vec3f &point = _defaultPoint, const Vec3f &normal = _defaultNormal, const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const Vec3f & point() const
    {
        return _point;
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    inline bool containsPoint(const Vec3f &point) const
    {
        return abs(_normal.dot(point) + _d) < EPS;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

private:
    Vec3f _point;  // ƽ�����ʾ�����еĵ�
    Vec3f _normal;  // ��λ������
    float _d;  // ƽ�����ʽ���̵ĳ�����

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultPoint;
    static const Vec3f _defaultNormal;

};


#endif
