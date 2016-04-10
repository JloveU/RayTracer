#include "Geometry.h"


const Vec3f Geometry::_defaultSurfaceColor = Vec3f(1.0, 1.0, 1.0);
const Vec3f Geometry::_defaultEmissionColor = Vec3f(0.0, 0.0, 0.0);
const float Geometry::_defaultTransparency = 0.0;
const float Geometry::_defaultReflection = 0.0;


Geometry::Geometry(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :_surfaceColor(surfaceColor)
    ,_emissionColor(emissionColor)
    ,_transparency(transparency)
    ,_reflection(reflection)
{
}
