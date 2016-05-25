#include "Polygon.h"
#include <stdexcept>


const Vec3f __defaultVertices[4] = {Vec3f(-1.0, 0.0, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(1.0, 2.0, 0.0), Vec3f(-1.0, 2.0, 0.0)};
const std::vector<Vec3f> Polygon::_defaultVertices(__defaultVertices, __defaultVertices + 4);


Polygon::Polygon(const std::vector<Vec3f> &vertices, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
    :Geometry(surfaceColor, emissionColor, transparency, specular, diffuse)
    ,_vertices(vertices)
{
    // ���������������3
    if (vertices.size() < 4)
    {
        throw std::runtime_error("Number of vertices in a Polygon must not be any value under 4!");
    }

    // ���㵥λ������
    Vec3f _edge1 = _vertices[1] - _vertices[0];
    Vec3f _edge2 = _vertices[2] - _vertices[1];
    _normal = _edge1.cross(_edge2);
    _normal.normalize();

    // ����������ƽ��
    _plane = Plane(_vertices[0], _normal, surfaceColor, emissionColor, transparency, specular);

    // ������ж����Ƿ���
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
    // ���ȼ����������������ƽ���Ƿ��н���
    float t = _plane.intersect(ray);
    if (t > 0)  // ����н���Ļ����жϽ����Ƿ��ڶ�����ڲ�
    {
        // �����ж���ͶӰ����άƽ�棨ͬʱ������ԭ��ƽ�Ƶ��ö��������ƽ������ߵĽ��㴦��
        Vec3f intersectionPoint = ray.pointAt(t);  // ���������ƽ������ߵĽ���
        std::vector<Vec2f> vertices2D(_vertices.size());
        if (_normal.x() != 0 && _normal.y() == 0 && _normal.z() == 0)  // ����ö��������ƽ��ƽ����yzƽ�棬��ֱ��ȥ�����ж����x����
        {
            for (unsigned i = 0; i < _vertices.size(); i++)
            {
                vertices2D[i].x() = _vertices[i].y() - intersectionPoint.y();
                vertices2D[i].y() = _vertices[i].z() - intersectionPoint.z();
            }
        }
        else if (_normal.x() == 0 && _normal.y() != 0 && _normal.z() == 0)  // ����ö��������ƽ��ƽ����xzƽ�棬��ֱ��ȥ�����ж����y����
        {
            for (unsigned i = 0; i < _vertices.size(); i++)
            {
                vertices2D[i].x() = _vertices[i].x() - intersectionPoint.x();
                vertices2D[i].y() = _vertices[i].z() - intersectionPoint.z();
            }
        }
        else  // ����ö��������ƽ��ƽ����xyƽ�棬����������������㣬�����ж���ͶӰ��xyƽ�棬��ֱ��ȥ�����ж����z����
        {
            for (unsigned i = 0; i < _vertices.size(); i++)
            {
                vertices2D[i].x() = _vertices[i].x() - intersectionPoint.x();
                vertices2D[i].y() = _vertices[i].y() - intersectionPoint.y();
            }
        }

        // �ý������㷨������Ľ���ָ����2άͶӰƽ����x�������εıߵĽ��㣩�жϽ����Ƿ��ڶ�����ڲ�
        float crossCount = 0;  // 2άͶӰƽ�棨�ѽ�ԭ��ƽ�Ƶ��ö��������ƽ������ߵĽ��㴦��x����������2άͶӰ����θ��ߵĽ�����Ŀ
        unsigned verticesNum = vertices2D.size();
        for (unsigned i = 0, j = 1; i < verticesNum; i++, j = (i == verticesNum-1) ? 0 : i+1)
        {
            Vec2f &v1 = vertices2D[i];
            Vec2f &v2 = vertices2D[j];
            if (v1.y() * v2.y() < 0)  // ������˵��y�������0���ҷ�����ͬ������������ X ���������޽���
            {
                if (v1.x() - v1.y() * (v2.x()-v1.x()) / (v2.y()-v1.y()) > 0)  // ����ñ���x���������н���
                {
                    crossCount++;
                }
            }
//             else if (v1.y() == 0)  // ����ñߵ�����һ���˵�����x���ϣ��������һ�˵��y�����жϣ���������ཻ0.5�Σ���������ཻ-0.5�Σ�TODO ʵ�����к�����Ҫ����������жϣ���֪Ϊ�Σ�
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
//             else if (v2.y() == 0)  // ͬ��
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
        if ((int)crossCount % 2 == 1)  // ���������Ϊ�������򽻵��ڶ�����ڲ�
        {
            normal = _normal;
            color = surfaceColor();  // TODO ��������
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
