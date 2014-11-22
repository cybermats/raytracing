#include "pointlight.h"
#include "scene.h"
#include "ray.h"

PointLight::PointLight(Scene* scene, Vec3d position, Color color)
        : _scene(scene)
        , _position(std::move(position))
        , _color(std::move(color))

{
}


Color PointLight::color() const {
    return _color;
}

Vec3d PointLight::direction(const Vec3d &point) const {
    return normalize(_position - point);
}

Color PointLight::shade(const Vec3d &point) const {
    Vec3d lightDir = _position - point;
    double distance = length(lightDir);
    lightDir /= distance;
    Ray ray(point + 0.000001 * lightDir, lightDir);

    if(_scene->hit(ray, distance))
        return Color(0, 0, 0, 1);

    return _color;
}
