#include "pointlight.h"
#include "scene.h"

PointLight::PointLight(Vec3d position, Color color)
: _position(std::move(position)), _color(std::move(color)) {
}


Color PointLight::color() const {
    return _color;
}

Vec3d PointLight::direction(const Vec3d &point) const {
    return normalize(_position - point);
}
