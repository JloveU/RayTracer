#ifndef VECTOR_H
#define VECTOR_H


#include <math.h>


// 三维向量类型
template<typename T>
class Vec3_
{

public:
    Vec3_()
        :x(T(0))
        ,y(T(0))
        ,z(T(0))
    {
    }

    Vec3_(T _x)
        :x(_x)
        ,y(_x)
        ,z(_x)
    {
    }

    Vec3_(T _x, T _y, T _z)
        :x(_x)
        ,y(_y)
        ,z(_z)
    {
    }

    inline Vec3_<T> operator + (const Vec3_<T> &v) const
    {
        return Vec3_<T>(x + v.x, y + v.y, z + v.z);
    }

    inline Vec3_<T> operator - (const Vec3_<T> &v) const
    {
        return Vec3_<T>(x - v.x, y - v.y, z - v.z);
    }

    inline Vec3_<T> operator * (const T v) const
    {
        return Vec3_<T>(x * v, y * v, z * v);
    }

    inline Vec3_<T> operator * (const Vec3_<T> &v) const
    {
        return Vec3_<T>(x * v.x, y * v.y, z * v.z);
    }

    inline T dot(const Vec3_<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline Vec3_<T> cross(const Vec3_<T> &v) const
    {
        return Vec3_<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    inline Vec3_<T> & operator += (const Vec3_<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vec3_<T> & operator *= (const T v)
    {
        x *= v;
        y *= v;
        z *= v;
        return *this;
    }

    inline Vec3_<T> & operator *= (const Vec3_<T> &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    inline Vec3_<T> operator - () const
    {
        return Vec3_<T>(-x, -y, -z);
    }

    inline T length2() const
    {
        return x * x + y * y + z * z;
    }

    inline T length() const
    {
        return sqrt(length2());
    } 
    inline Vec3_<T> & normalize()
    {
        T norm = length();
        *this *= (norm ? 1.0/norm : 0.0);
        return *this;
    }

//     friend std::ostream & operator << (std::ostream &os, const Vec3_<T> &v)
//     {
//         os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
//         return os;
//     }

public:
    T x, y, z;

};

typedef Vec3_<float> Vec3f;


#endif
