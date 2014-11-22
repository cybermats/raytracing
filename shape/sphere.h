#pragma once

#include "igeometry.h"
#include "../vector.h"


class IMaterial;

class Sphere : public IGeometry
{
public:
    Sphere(Vec3d origin, double radius, IMaterial* material);

    virtual double intersect(const Ray &ray) const override;

    virtual void populate_intersection(Intersection &intersection) const override;

    virtual IMaterial* material() const override;

private:
    Vec3d _origin;
    double _radius;
    IMaterial* _material;
};

