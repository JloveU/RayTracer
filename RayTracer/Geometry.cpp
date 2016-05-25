#include "Geometry.h"
#include <stdexcept>


const Vec3f Geometry::_defaultSurfaceColor = Vec3f(1.0, 1.0, 1.0);
const Vec3f Geometry::_defaultEmissionColor = Vec3f(0.0, 0.0, 0.0);
const float Geometry::_defaultTransparency = 0.0;
const float Geometry::_defaultSpecular = 0.0;
const float Geometry::_defaultDiffuse = 1.0;


Geometry::Geometry(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float specular, const float diffuse)
{
    // 颜色值必须大于等于0
    if (surfaceColor.x() < 0 || surfaceColor.y() < 0 || surfaceColor.z() < 0 || emissionColor.x() < 0 || emissionColor.y() < 0 || emissionColor.z() < 0)
    {
        throw std::runtime_error("Value of color must not be under 0!");
    }

    // 透明度必须大于等于0
    if (transparency < 0)
    {
        throw std::runtime_error("Value of transparency must not be under 0!");
    }

    // 镜面反射系数必须大于等于0
    if (specular < 0)
    {
        throw std::runtime_error("Value of specular must not be under 0!");
    }

    // 漫反射系数必须大于等于0
    if (diffuse < 0)
    {
        throw std::runtime_error("Value of diffuse must not be under 0!");
    }

    _surfaceColor = surfaceColor;
    _emissionColor = emissionColor;
    _transparency = transparency;
    _specular = specular;
    _diffuse = diffuse;
}


void Geometry::setTexture(const std::string &textureKey)
{
    const shared_ptr<const cv::Mat> textureImage = TexturePool::instance().get(textureKey);
    if (!textureImage)
    {
        throw std::runtime_error("There is no texture named " + textureKey + "!");
    }

    _textureImage = textureImage;
}


void Geometry::transform(const Mat4f &t)
{
}


Geometry::~Geometry()
{
}
