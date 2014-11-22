#pragma once

#include "vector.h"
#include "ray.h"
#include "shape/ishape.h"

#include <ostream>

class IShape;

class Intersection
{
public:
    explicit Intersection(Ray ray, double t)
        : _ray(std::move(ray))
        , _t(t)
        , _point(ray.origin() + (t * ray.direction()))
    {}

    const Ray& ray() const
    {
        return _ray;
    }

    double t() const
    {
        return _t;
    }

    const Vec3d& normal() const
    {
        return _normal;
    }

    void normal(const Vec3d& n)
    {
        _normal = n;
    }

    const Vec3d& point() const
    {
        return _point;
    }

    void point(const Vec3d& p)
    {
        _point = p;
    }

    const IShape* shape() const
    {
        return _shape;
    }

    void shape(const IShape* shape)
    {
        _shape = shape;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Intersection& i)
    {
        stream << "Intersection(ray: " << i._ray << ", t: " << i._t << ", normal: " << i._normal << ", point: " << i._point << ")";
        return stream;
    }

private:
    Ray _ray;
    double _t;
    Vec3d _normal;
    Vec3d _point;
    const IShape* _shape;

};