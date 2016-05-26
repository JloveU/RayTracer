#include "Triangle.h"
#include <stdexcept>
#include <opencv.hpp>


const Vec3f Triangle::_defaultVertices[3] = {Vec3f(-1.0, 0.0, 0.0), Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 1.732, 0.0)};


Triangle::Triangle(const Vec3f &vertex0, const Vec3f &vertex1, const Vec3f &vertex2, const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
    :Geometry(surfaceColor, emissionColor, transparency, specular, diffuse)
{
    // �κ��������㲻���غ�
    if (vertex0 == vertex1 || vertex1 == vertex2 || vertex2 == vertex0)
    {
        throw std::runtime_error("There should not be two vertices in a Triangle which have same coordinates!");
    }

    _vertices[0] = vertex0;
    _vertices[1] = vertex1;
    _vertices[2] = vertex2;

    updateCache();
}


void Triangle::updateCache()
{
    // ����������
    _edge1 = _vertices[0] - _vertices[1];
    _edge2 = _vertices[0] - _vertices[2];

    // ���㵥λ������
    _normal = _edge1.cross(_edge2);
    _normal.normalize();
}


void Triangle::setTextureCoordinates(const Vec2f &textureCoordinate0, const Vec2f &textureCoordinate1, const Vec2f &textureCoordinate2)
{
    if (!hasTexture())
    {
        throw std::runtime_error("Texture should be set before set texture coordinate!");
    }

    _textureCoordinates.resize(3);
    _textureCoordinates[0] = textureCoordinate0;
    _textureCoordinates[1] = textureCoordinate1;
    _textureCoordinates[2] = textureCoordinate2;
}


void Triangle::transform(const Mat4f &t)
{
    for (unsigned i = 0; i < 3; i++)
    {
        Matrix::transform(_vertices[i], t);
    }

    updateCache();
}


float Triangle::intersect(const Ray &ray, Vec3f &normal, Vec3f &color) const
{
    Vec3f s = _vertices[0] - ray.origin();
    float inv = (float)1 / Matrix::det(ray.direction(), _edge1, _edge2);
    float t = Matrix::det(s, _edge1, _edge2) * inv;
    float beta = Matrix::det(ray.direction(), s, _edge2) * inv;
    float gamma = Matrix::det(ray.direction(), _edge1, s) * inv;
    if (t > 0 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && beta + gamma <= 1)
    {
        normal = _normal;

        if (!_textureCoordinates.empty())  // �������������������ɫ
        {
            Vec2f textureCoordinate = _textureCoordinates[0] * (1 - beta - gamma) + _textureCoordinates[1] * beta + _textureCoordinates[2] * gamma;

            // �������������������1���������ʹ����������Ѱַģʽ���ο���http://blog.csdn.net/soief/article/details/5714912��
            for (unsigned i = 0; i < 2; i++)
            {
                if (textureCoordinate[i] < 0.0)
                {
                    textureCoordinate[i] = 0.0;
                }
                if (textureCoordinate[i] > 1.0)
                {
                    // Wrapping����Ѱַģʽ
                    textureCoordinate[i] = textureCoordinate[i] - int(textureCoordinate[i]);
                }
            }

            cv::Vec3b rgb = texture()->at<cv::Vec3b>(int(textureCoordinate.y() * (texture()->rows-1)), int(textureCoordinate.x() * (texture()->cols-1)));
            for (unsigned i = 0; i < 3; i++)
            {
                color[i] = (float)rgb[2 - i] / 255;
            }
        }
        else  // ����������ֱ�ӷ��ر�����ɫ
        {
            color = surfaceColor();
        }

        return t;
    }
    else
    {
        return -1;
    }
}
