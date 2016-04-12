#ifndef GEOMETRYUNION_H
#define GEOMETRYUNION_H


#include <vector>
#include "Vector.h"
#include "Geometry.h"
#include "Ray.h"


// �ɶ���������ǲ�ͬ���͵ģ�����ͼ����ϳɵ��µļ���ͼ�Σ��Ӽ���ͼ�εĸ���������ԣ���ɫ�ȣ�ʧЧ
class GeometryUnion : public Geometry
{

public:
    GeometryUnion(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float reflection = _defaultReflection);

    inline const std::vector<Geometry *> & geometries() const
    {
        return _geometries;
    }

    // ��Ӽ���ͼ��
    void addGeometry(Geometry *geometry);

    // ɾ�����м���ͼ��
    void removeAllGeometries();

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f()) const;

protected:
    std::vector<Geometry *> _geometries;

};


#endif
