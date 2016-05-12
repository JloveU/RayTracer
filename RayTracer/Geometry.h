#ifndef GEOMETRY_H
#define GEOMETRY_H


#include <string>
#include "Vector.h"
#include "Ray.h"


// ��������������ĸ���
class Geometry
{

public:
    Geometry(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float reflection = _defaultReflection);

    // ʵ�ֶ�̬��;�ĸ�������д��������������������ж���(��.cpp�ļ���)����������ӳ���,���������ڴ�й©
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

    inline float reflection() const
    {
        return _reflection;
    }

    inline void setTextureFileName(const std::string &textureFileName)
    {
        _textureFileName = textureFileName;
    }

    inline const std::string & textureFileName() const
    {
        return _textureFileName;
    }

    inline bool hasTextureFile() const
    {
        return !_textureFileName.empty();
    }

    // ������ߺ͸�����ĵ�1������
    // ray: (����)����
    // normal: (���)���㴦�ĵ�λ������(ָ�򼸺�����������)�����޽����򲻸ı������normal
    // color: (���)���㴦����ɫ������������Ϊ������������ɫ������������ΪsurfaceColor�����޽����򲻸ı������color
    // ���ؽ����Ӧ�ĸù��ߵ�ʱ��t���ӹ���ԭ�㵽����ĳ��ȣ������޽����򷵻�-1
    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const =0;

private:
    Vec3f _surfaceColor;  // ������ɫ
    Vec3f _emissionColor;  // ������ɫ
    float _transparency;  // ͸����
    float _reflection;  // ����ϵ��
    std::string _textureFileName;  // ����ͼƬ�ļ���·��

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultSurfaceColor;
    static const Vec3f _defaultEmissionColor;
    static const float _defaultTransparency;
    static const float _defaultReflection;

};


#endif
