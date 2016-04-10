#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"


// ����
class Scene
{

public:
    Scene(const Vec3f &backgroundColor=Vec3f(1.0, 1.0, 1.0));

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

private:
    Vec3f _backgroundColor;
    std::vector<Geometry *> _geometries;

};


#endif
