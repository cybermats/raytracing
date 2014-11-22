#pragma once

#include "color.h"
#include "vector.h"


class ILightSource
{
public:
    virtual Color color() const = 0;
    virtual Vec3d direction(const Vec3d& point) const = 0;
    virtual Color shade(const Vec3d& point) const = 0;

};