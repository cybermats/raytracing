#define _USE_MATH_DEFINES

#include "sphere.h"
#include "../ray.h"
#include "../intersection.h"
#include "../shader/ishader.h"
#include "../scene.h"

#include <cmath>


Sphere::Sphere(Vec3d origin, double radius, const std::string& shaderName)
        : _origin(std::move(origin))
        , _radius(radius)
        , _shaderName(shaderName)
        , _shader(nullptr)
{}


double Sphere::intersect(const Ray &ray) const {

    const Vec3d& o = ray.origin();
    const Vec3d& d = ray.direction();

    double dx = d.x;
    double dy = d.y;
    double dz = d.z;
    double ox = o.x;
    double oy = o.y;
    double oz = o.z;
    double orx = _origin.x;
    double ory = _origin.y;
    double orz = _origin.z;

    const double a = 1;
    double b = 2 * (dx *(ox - orx) + dy * (oy - ory) + dz * (oz - orz));
    double c = (ox - orx) * (ox - orx) +
            (oy - ory) * (oy - ory) +
            (oz - orz) * (oz - orz) -
            _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0.0)
        return -1;

    double inv_disc = sqrt(discriminant);
    double t = (-b - inv_disc) / 2 * a;

    if(t > 0)
        return t;
    t = (-b + inv_disc) / 2 * a;
    return t;
}

void Sphere::populate_intersection(Intersection &intersection) const {
    assert(intersection.t() >= 0);
    double inv_radius = 1 / _radius;
    Vec3d normal = (intersection.point() - _origin) * inv_radius;
    intersection.normal(normal);
    intersection.shape(this);

    Vec3d d = -normal;
    Vec2d uv(0.5 + atan2(d.z, d.x)/(2 * M_PI),
            0.5 - asin(d.y) / M_PI);

    intersection.uv(uv);
}

const IShader * Sphere::shader() const {
    assert(_shader);
    return _shader;
}

void Sphere::initialize(const Scene &scene) {
    _shader = scene.get_shader(_shaderName);
}
