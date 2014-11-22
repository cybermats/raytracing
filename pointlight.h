#pragma once

#include "ilightsource.h"
#include "color.h"
#include "vector.h"
#include "scene.h"
#include <memory>

class PointLight : public ILightSource
{
public:
    PointLight(Scene* scene, Vec3d position, Color color);

    virtual Color color() const override;

    virtual Color shade(const Vec3d &point) const override;

    virtual Vec3d direction(const Vec3d &point) const override;

private:
    Scene* _scene;
    Vec3d _position;
    Color _color;
};

