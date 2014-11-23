#include "plane.h"
#include "../shader/ishader.h"
#include "../scene.h"


Plane::Plane(Vec3d normal, double location, const std::string& shaderName)
        : _normal(normal)
        , _location(location)
        , _shaderName(shaderName)
        , _shader(nullptr)
{}

double Plane::intersect(const Ray &ray) const {
    float nDotO = dot(_normal, ray.origin());
    float nDotD = dot(_normal, ray.direction());

    return (_location - nDotO)/nDotD;
}

void Plane::populate_intersection(Intersection &intersection) const {
    assert(intersection.t() >= 0);
    intersection.normal(_normal);
    intersection.shape(this);
    Vec3d u;
    if(_normal.x != 0 || _normal.y != 0)
        u = normalize(Vec3d(_normal.y, -_normal.x, 0));
    else
        u = normalize(Vec3d(-_normal.z, 0, _normal.x));
    auto v = cross(_normal, u);

    Vec2d uv(dot(u, intersection.point()),
            dot(v, intersection.point()));
    intersection.uv(uv);
}

const IShader *Plane::shader() const {
    assert(_shader);
    return _shader;
}

void Plane::initialize(const Scene &scene) {
    _shader = scene.get_shader(_shaderName);
}
