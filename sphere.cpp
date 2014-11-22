#include "sphere.h"
#include "ray.h"
#include "intersection.h"


double Sphere::intersect(const Ray &ray) {

    Vec3d o = ray.origin();
    Vec3d d = ray.direction();

    const double a = 1;
    double b = 2 * (d[0] *(o[0] - _origin[0]) + d[1] * (o[1] - _origin[1]) + d[2] * (o[2] - _origin[2]));
    double c = (o[0] - _origin[0]) * (o[0] - _origin[0]) +
            (o[1] - _origin[1]) * (o[1] - _origin[1]) +
            (o[2] - _origin[2]) * (o[2] - _origin[2]) -
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

void Sphere::populate_intersection(Intersection &intersection) {
    assert(intersection.t() >= 0);
    double inv_radius = 1 / _radius;
    intersection.normal((intersection.point() - _origin) * inv_radius);
    intersection.shape(this);
}
