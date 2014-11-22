#include "plane.h"
#include "../material/imaterial.h"



Plane::Plane(Vec3d normal, double location, IMaterial *material)
: _normal(normal), _location(location), _material(material) {
}

double Plane::intersect(const Ray &ray) const {
    float nDotO = dot(_normal, ray.origin());
    float nDotD = dot(_normal, ray.direction());

    return (_location - nDotO)/nDotD;
}

void Plane::populate_intersection(Intersection &intersection) const {
    assert(intersection.t() >= 0);
    intersection.normal(_normal);
    intersection.shape(this);
}

IMaterial *Plane::material() const {
    return _material;
}
