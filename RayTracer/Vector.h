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

    // 将操作符方法的返回类型声明为const，是为了防止出现“if ((a + b) = c)”中误把“==”写成“=”的错误
    inline const Vec3_<T> operator + (const Vec3_<T> &v) const
    {
        return Vec3_<T>(x + v.x, y + v.y, z + v.z);
    }

    inline const Vec3_<T> operator - (const Vec3_<T> &v) const
    {
        return Vec3_<T>(x - v.x, y - v.y, z - v.z);
    }

    inline const Vec3_<T> operator * (const T v) const
    {
        return Vec3_<T>(x * v, y * v, z * v);
    }

    inline const Vec3_<T> operator * (const Vec3_<T> &v) const
    {
        return Vec3_<T>(x * v.x, y * v.y, z * v.z);
    }

    inline const T dot(const Vec3_<T> &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline const Vec3_<T> cross(const Vec3_<T> &v) const
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

    inline const Vec3_<T> operator - () const
    {
        return Vec3_<T>(-x, -y, -z);
    }

    inline const bool operator == (const Vec3_<T> &v) const
    {
        return (x == v.x && y == v.y && z == v.z);
    }

    inline const T length2() const
    {
        return x * x + y * y + z * z;
    }

    inline const T length() const
    {
        return sqrt(length2());
    }

    inline Vec3_<T> & normalize()
    {
        T norm = length();
        *this *= (norm ? 1.0/norm : 0.0);
        return *this;
    }

    // 计算由3个输入的列向量组成的3*3矩阵的行列式
    inline static const T det(const Vec3_<T> &v1, const Vec3_<T> &v2, const Vec3_<T> &v3)
    {
        return v1.x * (v2.y*v3.z-v2.z*v3.y) - v1.y * (v2.x*v3.z-v2.z*v3.x) + v1.z * (v2.x*v3.y-v2.y*v3.x);
    }

//     friend std::ostream & operator << (std::ostream &os, const Vec3_<T> &v)
//     {
//         os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
//         return os;
//     }

public:
    union
    {
        struct
        {
            T x, y, z;
        };
        T val[3];
    };

};


// 二维向量类型
template<typename T>
class Vec2_
{

public:
    Vec2_()
        :x(T(0))
        ,y(T(0))
    {
    }

    Vec2_(T _x)
        :x(_x)
        ,y(_x)
    {
    }

    Vec2_(T _x, T _y)
        :x(_x)
        ,y(_y)
    {
    }

    inline const Vec2_<T> operator + (const Vec2_<T> &v) const
    {
        return Vec2_<T>(x + v.x, y + v.y);
    }

    inline const Vec2_<T> operator - (const Vec2_<T> &v) const
    {
        return Vec2_<T>(x - v.x, y - v.y);
    }

    inline const Vec2_<T> operator * (const T v) const
    {
        return Vec2_<T>(x * v, y * v);
    }

    inline const Vec2_<T> operator * (const Vec2_<T> &v) const
    {
        return Vec2_<T>(x * v.x, y * v.y);
    }

    inline const T dot(const Vec2_<T> &v) const
    {
        return x * v.x + y * v.y;
    }

    inline Vec2_<T> & operator += (const Vec2_<T> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    inline Vec2_<T> & operator *= (const T v)
    {
        x *= v;
        y *= v;
        return *this;
    }

    inline Vec2_<T> & operator *= (const Vec2_<T> &v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    inline const Vec2_<T> operator - () const
    {
        return Vec2_<T>(-x, -y);
    }

    inline const bool operator == (const Vec2_<T> &v) const
    {
        return (x == v.x && y == v.y);
    }

    inline const T length2() const
    {
        return x * x + y * y;
    }

    inline const T length() const
    {
        return sqrt(length2());
    }

    inline Vec2_<T> & normalize()
    {
        T norm = length();
        *this *= (norm ? 1.0/norm : 0.0);
        return *this;
    }

public:
    union
    {
        struct
        {
            T x, y;
        };
        T val[2];
    };

};


typedef Vec3_<float> Vec3f;
typedef Vec2_<float> Vec2f;
typedef Vec3_<int> Vec3i;
typedef Vec2_<int> Vec2i;


#endif
