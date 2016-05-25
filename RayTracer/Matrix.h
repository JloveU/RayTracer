#ifndef VECTOR_H
#define VECTOR_H


#include <math.h>
#include <Eigen\Dense>


typedef Eigen::Vector3f Vec3f;
typedef Eigen::Vector3i Vec3i;
typedef Eigen::Vector2f Vec2f;
typedef Eigen::Vector2i Vec2i;

// typedef Eigen::Matrix4f Mat4f;

// 计算由3个输入的列向量组成的3*3矩阵的行列式
float det(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3);


#endif
