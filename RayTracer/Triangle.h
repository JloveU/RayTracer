#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <vector>
#include <stdexcept>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "shared_ptr.h"


// ������
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
    // ��������������¼���������Ա����
    void updateCache();

private:
    Vec3f _vertices[3];  // �����ε�3�����㣨����ʱ�뷽��ȷ�����棩
    Vec3f _edge1, _edge2;  // �ֱ�Ϊ�����ε������ߣ����ڼ�������ߵĽ���
    Vec3f _normal;  // ��λ������
    std::vector<Vec2f> _textureCoordinates;  // �����ε�3���������������

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultVertices[3];

};


#endif
