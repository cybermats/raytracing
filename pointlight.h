#pragma once

#include "ilightsource.h"
#include "color.h"
#include "vector.h"
#include "scene.h"
#include <memory>

class PointLight : public ILightSource
{
public:
    PointLight(Vec3d position, Color color);


    virtual Color color() const override;

    virtual Vec3d direction(const Vec3d &point) const override;

private:
    Vec3d _position;
    Color _color;
};

