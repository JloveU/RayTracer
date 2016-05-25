#include "Polygon.h"
#include <stdexcept>


const Vec3f __defaultVertices[4] = {Vec3f(-1.0, 0.0, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(1.0, 2.0, 0.0), Vec3f(-1.0, 2.0, 0.0)};
const std::vector<Vec3f> Polygon::_defaultVertices(__defaultVertices, __defaultVertices + 4);


Polygon::Polygon(const std::vector<Vec3f> &vertices, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
    :Geometry(surfaceColor, emissionColor, transparency, specular, diffuse)
    ,_vertices(vertices)
{
    // 顶点数量必须大于3
    if (vertices.size() < 4)
    {
        throw std::runtime_error("Number of vertices in a Polygon must not be any value under 4!");
    }

    // 计算单位法向量
    Vec3f _edge1 = _vertices[1] - _vertices[0];
    Vec3f _edge2 = _vertices[2] - _vertices[1];
    _normal = _edge1.cross(_edge2);
    _normal.normalize();

    // 计算其所在平面
    _plane = Plane(_vertices[0], _normal, surfaceColor, emissionColor, transparency, specular);

    // 检查所有顶点是否共面
    for (unsigned i = 0; i < _vertices.size(); i++)
    {
        if (!_plane.containsPoint(_vertices[i]))
        {
            throw std::runtime_error("All the vertices in a Polygon must be on one plane!");
        }
    }
}


float Polygon::intersect(const Ray &ray, Vec3f &normal, Vec3f &color) const
{
    // 首先计算光线与多边形所在平面是否有交点
    float t = _plane.intersect(ray);
    if (t > 0)  // 如果有交点的话，判断交点是否在多边形内部
    {
        // 将所有顶点投影到二维平面（同时将坐标原点平移到该多边形所在平面与光线的交点处）
        Vec3f intersectionPoint = ray.pointAt(t);  // 多边形所在平面与光线的交点
        std::vector<Vec2f> vertices2D(_vertices.size());
        if (_normal.x() != 0 && _normal.y() == 0 && _normal.z() == 0)  // 如果该多边形所在平面平行于yz平面，则直接去掉所有顶点的x分量
        {
            for (unsigned i = 0; i < _vertices.size(); i++)
            {
                vertices2D[i].x() = _vertices[i].y() - intersectionPoint.y();
                vertices2D[i].y() = _vertices[i].z() - intersectionPoint.z();
            }
        }
        else if (_normal.x() == 0 && _normal.y() != 0 && _normal.z() == 0)  // 如果该多边形所在平面平行于xz平面，则直接去掉所有顶点的y分量
        {
            for (unsigned i = 0; i < _vertices.size(); i++)
            {
                vertices2D[i].x() = _vertices[i].x() - intersectionPoint.x();
                vertices2D[i].y() = _vertices[i].z() - intersectionPoint.z();
            }
        }
        else  // 如果该多边形所在平面平行于xy平面，或以上情况均不满足，则将所有顶点投影至xy平面，即直接去掉所有顶点的z分量
        {
            for (unsigned i = 0; i < _vertices.size(); i++)
            {
                vertices2D[i].x() = _vertices[i].x() - intersectionPoint.x();
                vertices2D[i].y() = _vertices[i].y() - intersectionPoint.y();
            }
        }

        // 用交点检测算法（这里的交点指的是2维投影平面上x轴与多边形的边的交点）判断交点是否在多边形内部
        float crossCount = 0;  // 2维投影平面（已将原点平移到该多边形所在平面与光线的交点处）x轴正半轴与2维投影多边形各边的交点数目
        unsigned verticesNum = vertices2D.size();
        for (unsigned i = 0, j = 1; i < verticesNum; i++, j = (i == verticesNum-1) ? 0 : i+1)
        {
            Vec2f &v1 = vertices2D[i];
            Vec2f &v2 = vertices2D[j];
            if (v1.y() * v2.y() < 0)  // 如果两端点的y坐标均非0，且符号相同，则这条边与 X 轴正半轴无交点
            {
                if (v1.x() - v1.y() * (v2.x()-v1.x()) / (v2.y()-v1.y()) > 0)  // 如果该边与x轴正半轴有交点
                {
                    crossCount++;
                }
            }
//             else if (v1.y() == 0)  // 如果该边的其中一个端点落在x轴上，则根据另一端点的y坐标判断，若正则计相交0.5次，若负则计相交-0.5次（TODO 实际运行好像不需要这种情况的判断，不知为何）
//             {
//                 if (v2.y() > 0)
//                 {
//                     crossCount += 0.5;
//                 } 
//                 else if (v2.y() < 0)
//                 {
//                     crossCount -= 0.5;
//                 }
//             }
//             else if (v2.y() == 0)  // 同上
//             {
//                 if (v1.y() > 0)
//                 {
//                     crossCount += 0.5;
//                 } 
//                 else if (v1.y() < 0)
//                 {
//                     crossCount -= 0.5;
//                 }
//             }
        }
        if ((int)crossCount % 2 == 1)  // 如果交点数为奇数，则交点在多边形内部
        {
            normal = _normal;
            color = surfaceColor();  // TODO 处理纹理
            return t;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

}
