#ifndef MATRIX_H
#define MATRIX_H


#include <Eigen\Dense>


typedef Eigen::Vector4f Vec4f;
typedef Eigen::Vector3f Vec3f;
typedef Eigen::Vector3i Vec3i;
typedef Eigen::Vector2f Vec2f;
typedef Eigen::Vector2i Vec2i;

typedef Eigen::Matrix4f Mat4f;  // 4×4浮点矩阵


namespace Matrix
{

    // 计算由3个输入的列向量组成的3*3矩阵的行列式
    float det(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3);

    // 生成旋转变换矩阵
    Mat4f formRotateMatrix(const Vec3f &axis, const float angle);

    // 空间变换
    void transform(Vec3f &vector, const Mat4f &t);

}


#endif
