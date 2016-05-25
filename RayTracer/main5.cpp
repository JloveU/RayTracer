#include <iostream>
#include <Eigen\Dense>


typedef Eigen::Vector3f Vec3f;
typedef Eigen::Matrix3f Mat3f;


// 测试Eigen::Vector3f
int main()
{
    Vec3f v1;
    v1[0] = 2;
    Vec3f v2(0, 1, 0);
    Vec3f v3 = v1 + v2;
    Vec3f v4 = v1 - v2;
    Vec3f v5 = v1 * 1.5;
    Vec3f v6 = v1 * v2;
    float f1 = v1.dot(v2);
    Vec3f v7 = v1.cross(v2);
    v7 = v1.cross3(v2);
    Vec3f v8 = v1; v8 += v2;
    Vec3f v9 = v1; v9 *= v2;
    Vec3f v10 = v1; v10 *= 1.5;
    Vec3f v11 = v1; v11 = -v11;
    bool b1 = v1 == v2, b2 = v1 == v1;
    float f2 = v1.norm();
    Vec3f v12 = v1.normalized();
    v1.normalize();
    v1.x();
    Mat3f m1(1, 2, 3);
    float f3 = m1.determinant();

    std::cout << "按回车键退出..." << std::endl;
    std::cin.get();

    return 0;
}
