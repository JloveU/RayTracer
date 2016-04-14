#ifndef MESH_H
#define MESH_H


#include <vector>
#include "Vector.h"
#include "GeometryUnion.h"
#include "Ray.h"


// 由三角面片构成的复杂几何图形
class Mesh : public GeometryUnion
{

public:
    Mesh(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float reflection = _defaultReflection);

    // 读取obj模型文件
    // 正确读取完毕返回0，出错返回-1
    int loadObj(const std::string &filename);

};


#endif
