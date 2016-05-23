#include "Geometry.h"
#include <stdexcept>


const Vec3f Geometry::_defaultSurfaceColor = Vec3f(1.0, 1.0, 1.0);
const Vec3f Geometry::_defaultEmissionColor = Vec3f(0.0, 0.0, 0.0);
const float Geometry::_defaultTransparency = 0.0;
const float Geometry::_defaultSpecular = 0.0;
const float Geometry::_defaultDiffuse = 1.0;


Geometry::Geometry(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
{
    // ��ɫֵ������ڵ���0
    if (surfaceColor.x < 0 || surfaceColor.y < 0 || surfaceColor.z < 0 || emissionColor.x < 0 || emissionColor.y < 0 || emissionColor.z < 0)
    {
        throw std::runtime_error("Value of color must not be under 0!");
    }

    // ͸���ȱ�����ڵ���0
    if (transparency < 0)
    {
        throw std::runtime_error("Value of transparency must not be under 0!");
    }

    // ���淴��ϵ��������ڵ���0
    if (specular < 0)
    {
        throw std::runtime_error("Value of specular must not be under 0!");
    }

    // ������ϵ��������ڵ���0
    if (diffuse < 0)
    {
        throw std::runtime_error("Value of diffuse must not be under 0!");
    }

    _surfaceColor = surfaceColor;
    _emissionColor = emissionColor;
    _transparency = transparency;
    _specular = specular;
    _diffuse = diffuse;

    _textureFileName.clear();
}

Geometry::~Geometry()
{
}
