#include "Geometry.h"


Geometry::Geometry(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :_surfaceColor(surfaceColor)
    ,_emissionColor(emissionColor)
    ,_transparency(transparency)
    ,_reflection(reflection)
{
}
