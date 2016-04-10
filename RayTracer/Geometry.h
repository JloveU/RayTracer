#ifndef GEOMETRY_H
#define GEOMETRY_H


#include "Vector.h"
#include "Ray.h"


// 场景中所有物体的父类
class Geometry
{

public:
    Geometry(const Vec3f &surfaceColor=Vec3f(1.0, 1.0, 1.0), const Vec3f &emissionColor = Vec3f(0.0, 0.0, 0.0), const float transparency = 0.0, const float reflection = 0.0);

    inline const Vec3f & surfaceColor() const
    {
        return _surfaceColor;
    }

    inline const Vec3f & emissionColor() const
    {
        return _emissionColor;
    }

    inline float transparency() const
    {
        return _transparency;
    }

    inline float reflection() const
    {
        return _reflection;
    }

    // 计算光线和该物体的第1个交点
    // ray: (输入)光线
    // normal: (输出)交点处的单位法向量(指向几何体外侧或正向)，若无交点则不改变输入的normal
    // 返回交点对应的该光线的时刻t（从光线原点到交点的长度），若无交点则返回-1
    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const =0;

private:
    Vec3f _surfaceColor;  // 表面颜色
    Vec3f _emissionColor;  // 发光颜色
    float _transparency;  // 透明度
    float _reflection;  // 反射系数

};


#endif
