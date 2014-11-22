#pragma once

#include "igeometry.h"
#include "../vector.h"

class Sphere : public IGeometry
{
public:
    Sphere(Vec3d origin, double radius)
            : _origin(std::move(origin)), _radius(radius)
    {}


    virtual double intersect(const Ray &ray) override;

    virtual void populate_intersection(Intersection &intersection) override;

private:
    Vec3d _origin;
    double _radius;
};

