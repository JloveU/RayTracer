#ifndef GEOMETRYUNION_H
#define GEOMETRYUNION_H


#include <vector>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "shared_ptr.h"


// �ɶ���������ǲ�ͬ���͵ģ�����ͼ����ϳɵ��µļ���ͼ�Σ��Ӽ���ͼ�εĸ���������ԣ���ɫ�ȣ�ʧЧ
class GeometryUnion : public Geometry
{

public:
    GeometryUnion(const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const std::vector<const shared_ptr<Geometry> > & geometries() const
    {
        return _geometries;
    }

    // ��Ӽ���ͼ��
    void addGeometry(const shared_ptr<Geometry> &geometry);

    // ɾ�����м���ͼ��
    void removeAllGeometries();

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

protected:
    std::vector<const shared_ptr<Geometry> > _geometries;

};


#endif
