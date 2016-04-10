#ifndef RAY_H
#define RAY_H


#include "Vector.h"


// ���ߣ����ߣ�
class Ray
{

public:
    Ray(const Vec3f &origin=Vec3f(0.0, 0.0, 0.0), const Vec3f &direction=Vec3f(0.0, 0.0, -1.0));

    inline const Vec3f & origin() const
    {
        return _origin;
    }

    inline const Vec3f & direction() const
    {
        return _direction;
    }

    // ���������ʱ��t�ﵽ�ĵ�
    inline Vec3f pointAt(const float t) const
    {
        return _origin + _direction * t;
    }

private:
    Vec3f _origin;
    Vec3f _direction;

};


#endif
