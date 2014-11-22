#pragma once

#include "ishape.h"
#include "../vector.h"


class IShader;

class Sphere : public IShape
{
public:
    Sphere(Vec3d origin, double radius, IShader * material);

    virtual double intersect(const Ray &ray) const override;

    virtual void populate_intersection(Intersection &intersection) const override;

    virtual IShader * material() const override;

private:
    Vec3d _origin;
    double _radius;
    IShader * _material;
};

