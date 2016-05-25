#ifndef RAY_H
#define RAY_H


#include "Matrix.h"


// ���ߣ����ߣ�
class Ray
{

public:
    Ray(const Vec3f &origin = _defaultOrigin, const Vec3f &direction = _defaultDirection);

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

public:
    // �����Ե�Ĭ��ֵ
    static const Vec3f _defaultOrigin;
    static const Vec3f _defaultDirection;

};


#endif
