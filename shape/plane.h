#pragma once

#include "ishape.h"
#include "../vector.h"
#include "../shader/ishader.h"
#include "../ray.h"
#include "../intersection.h"

class IShader;

class Plane : public IShape
{

public:
    Plane(Vec3d normal, double location, IShader *material);

    virtual double intersect(const Ray &ray) const override;
    virtual void populate_intersection(Intersection &intersection) const override;
    virtual IShader *material() const override;

private:
    Vec3d _normal;
    double _location;
    IShader * _material;
};

