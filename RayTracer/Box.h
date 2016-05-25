#ifndef BOX_H
#define BOX_H


#include <vector>
#include "Matrix.h"
#include "Geometry.h"
#include "Ray.h"
#include "Plane.h"


// ������
class Box : public Geometry
{

public:
    Box(const Vec3f &origin = _defaultOrigin, const Vec3f &size = _defaultSize, const Vec3f &surfaceColor = _defaultSurfaceColor, const Vec3f &emissionColor = _defaultEmissionColor, const float transparency = _defaultTransparency, const float specular = _defaultSpecular, const float diffuse = _defaultDiffuse);

    inline const Vec3f & origin() const
    {
        return _origin;
    }

    inline const Vec3f & size() const
    {
        return _size;
    }

    virtual float intersect(const Ray &ray, Vec3f &normal=Vec3f(), Vec3f &color=Vec3f()) const;

private:
    Vec3f _origin;  // ԭ�㣨�������ԭ��Ķ��㣩
    Vec3f _size;  // �ߴ磨�ֱ���x��y��z��ƽ�еıߵı߳���
    Plane _slabs[3][2];  // 3��ƽ���(Slab)�����ηֱ��Ӧ��ʼδ��ת״̬ʱ��yz��zx��xyƽ��

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultOrigin;
    static const Vec3f _defaultSize;

};


#endif
