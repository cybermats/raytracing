#pragma once

#include "ishape.h"
#include "../vector.h"
#include "../scene.h"


class IShader;
class Scene;

class Sphere : public IShape
{
public:
    Sphere(Vec3d origin, double radius, const std::string& shaderName );

    virtual double intersect(const Ray &ray) const override;

    virtual void populate_intersection(Intersection &intersection) const override;

    virtual const IShader * shader() const override;


    virtual void initialize(const Scene &scene) override;

private:
    Vec3d _origin;
    double _radius;
    std::string _shaderName;
    const IShader * _shader;
};

