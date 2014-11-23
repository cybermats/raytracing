#pragma once

#include "ishape.h"
#include "../vector.h"
#include "../shader/ishader.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"

class IShader;

class Plane : public IShape
{

public:
    Plane(Vec3d normal, double location, const std::string& shaderName);

    virtual double intersect(const Ray &ray) const override;
    virtual void populate_intersection(Intersection &intersection) const override;
    virtual const IShader *shader() const override;


    virtual void initialize(const Scene &scene) override;

private:
    Vec3d _normal;
    double _location;
    std::string _shaderName;
    const IShader * _shader;
};

