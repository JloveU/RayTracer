#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"


// ����
class Scene
{

public:
    Scene(const Vec3f &backgroundColor = _defaultBackgroundColor);

    inline const Vec3f & backgroundColor() const
    {
        return _backgroundColor;
    }

    inline const std::vector<Geometry *> & geometries() const
    {
        return _geometries;
    }

    // ��Ӽ���ͼ�ε�������
    void addGeometry(Geometry *geometry);

    // ɾ�������е����м���ͼ��
    void removeAllGeometries();

    // �������ϵ��־��������
    void addAxes();

private:
    Vec3f _backgroundColor;
    std::vector<Geometry *> _geometries;

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultBackgroundColor;

};


#endif
