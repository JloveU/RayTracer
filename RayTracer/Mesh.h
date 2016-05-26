#ifndef MESH_H
#define MESH_H


#include <vector>
#include "Matrix.h"
#include "GeometryUnion.h"
#include "Ray.h"


// ��������Ƭ���ɵĸ��Ӽ���ͼ��
class Mesh : public GeometryUnion
{

public:
    Mesh(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    // ��ȡobjģ���ļ�
    // ��ȷ��ȡ��Ϸ���0��������-1
    int loadObj(const std::string &filename);

    virtual void transform(const Mat4f &t);

};


#endif
