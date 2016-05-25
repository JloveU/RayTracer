#ifndef GEOMETRY_H
#define GEOMETRY_H


#include <string>
#include <opencv.hpp>
#include "Matrix.h"
#include "Ray.h"
#include "TexturePool.h"
#include "shared_ptr.h"


// 场景中所有物体的父类
class Geometry
{

public:
    Geometry(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    // 实现多态用途的父类必须有纯虚析构函数（但必须有定义(在.cpp文件中)，否则会链接出错）,否则会存在内存泄漏
    virtual ~Geometry() = 0;

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

    inline float specular() const
    {
        return _specular;
    }

    inline float diffuse() const
    {
        return _diffuse;
    }

    inline bool isLight() const
    {
        return _emissionColor.x() > 0 || _emissionColor.y() > 0 || _emissionColor.z() > 0;
    }

    void setTexture(const std::string &textureKey);

    inline const shared_ptr<const cv::Mat> & texture() const
    {
        return _textureImage;
    }

    inline bool hasTexture() const
    {
        return _textureImage;
    }

    // 空间变换，用于对几何图形进行旋转、平移等变换
    // t: 变换矩阵
    virtual void transform(const Mat4f &t);

    // 计算光线和该物体的第1个交点
    // ray: (输入)光线
    // normal: (输出)交点处的单位法向量(指向几何体外侧或正向)，若无交点则不改变输入的normal
    // color: (输出)交点处的颜色，若有纹理则为纹理坐标点的颜色，若无纹理则为surfaceColor，若无交点则不改变输入的color
    // 返回交点对应的该光线的时刻t（从光线原点到交点的长度），若无交点则返回-1
    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const =0;

private:
    Vec3f _surfaceColor;  // 表面颜色
    Vec3f _emissionColor;  // 发光颜色
    float _transparency;  // 透明度
    float _specular;  // 镜面反射系数
    float _diffuse;  // 漫反射系数
    shared_ptr<const cv::Mat> _textureImage;  // 纹理图像

public:
    // 各属性的默认值
    static const Vec3f _defaultSurfaceColor;
    static const Vec3f _defaultEmissionColor;
    static const float _defaultTransparency;
    static const float _defaultSpecular;
    static const float _defaultDiffuse;

};


#endif
