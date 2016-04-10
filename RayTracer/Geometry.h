#ifndef GEOMETRY_H
#define GEOMETRY_H


#include "Vector.h"
#include "Ray.h"


// ��������������ĸ���
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

    // ������ߺ͸�����ĵ�1������
    // ray: (����)����
    // normal: (���)���㴦�ĵ�λ������(ָ�򼸺�����������)�����޽����򲻸ı������normal
    // ���ؽ����Ӧ�ĸù��ߵ�ʱ��t���ӹ���ԭ�㵽����ĳ��ȣ������޽����򷵻�-1
    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const =0;

private:
    Vec3f _surfaceColor;  // ������ɫ
    Vec3f _emissionColor;  // ������ɫ
    float _transparency;  // ͸����
    float _reflection;  // ����ϵ��

};


#endif
