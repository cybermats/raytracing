#pragma once

#include "igeometry.h"
#include "../vector.h"
#include "../material/imaterial.h"
#include "../ray.h"
#include "../intersection.h"

class IMaterial;

class Plane : public IGeometry
{

public:
    Plane(Vec3d normal, double location, IMaterial *material);

    virtual double intersect(const Ray &ray) const override;
    virtual void populate_intersection(Intersection &intersection) const override;
    virtual IMaterial *material() const override;

private:
    Vec3d _normal;
    double _location;
    IMaterial* _material;
};

