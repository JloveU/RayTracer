#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "Matrix.h"
#include "Geometry.h"
#include "shared_ptr.h"


// ����
class Scene
{

public:
    Scene(const Vec3f &backgroundColor = _defaultBackgroundColor);

    inline const Vec3f & backgroundColor() const
    {
        return _backgroundColor;
    }

    inline const std::vector<const shared_ptr<Geometry> > & geometries() const
    {
        return _geometries;
    }

    // ��Ӽ���ͼ�ε�������
    void addGeometry(const shared_ptr<Geometry> &geometry);

    // ɾ�������е����м���ͼ��
    void removeAllGeometries();

    // �������ϵ��־��������
    void addAxes();

private:
    Vec3f _backgroundColor;
    std::vector<const shared_ptr<Geometry> > _geometries;

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultBackgroundColor;

};


#endif
