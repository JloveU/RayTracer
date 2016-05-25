#ifndef RAY_H
#define RAY_H


#include "Matrix.h"


// 光线（射线）
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

    // 计算光线在时刻t达到的点
    inline Vec3f pointAt(const float t) const
    {
        return _origin + _direction * t;
    }

private:
    Vec3f _origin;
    Vec3f _direction;

public:
    // 各属性的默认值
    static const Vec3f _defaultOrigin;
    static const Vec3f _defaultDirection;

};


#endif
