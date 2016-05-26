#ifndef MATRIX_H
#define MATRIX_H


#include <Eigen\Dense>


typedef Eigen::Vector4f Vec4f;
typedef Eigen::Vector3f Vec3f;
typedef Eigen::Vector3i Vec3i;
typedef Eigen::Vector2f Vec2f;
typedef Eigen::Vector2i Vec2i;

typedef Eigen::Matrix4f Mat4f;  // 4��4�������


namespace Matrix
{

    // ������3���������������ɵ�3*3���������ʽ
    float det(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3);

    // ������ת�任����
    Mat4f formRotateMatrix(const Vec3f &axis, const float angle);

    // �ռ�任
    void transform(Vec3f &vector, const Mat4f &t);

}


#endif
