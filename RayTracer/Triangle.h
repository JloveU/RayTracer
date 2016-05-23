#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <vector>
#include <stdexcept>
#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// ������
class Triangle : public Geometry
{

public:
    Triangle(const Vec3f &vertex0 = _defaultVertices[0], const Vec3f &vertex1 = _defaultVertices[1], const Vec3f &vertex2 = _defaultVertices[2], const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const Vec3f * vertices() const
    {
        return _vertices;
    }

    inline const Vec3f & normal() const
    {
        return _normal;
    }

    inline void setTextureCoordinates(const Vec2f &textureCoordinate0, const Vec2f &textureCoordinate1, const Vec2f &textureCoordinate2)
    {
        if (!hasTextureFile())
        {
            throw std::runtime_error("Texture file should be set before set texture coordinate!");
        }
        _textureCoordinates.resize(3);
        _textureCoordinates[0] = textureCoordinate0;
        _textureCoordinates[1] = textureCoordinate1;
        _textureCoordinates[2] = textureCoordinate2;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

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
