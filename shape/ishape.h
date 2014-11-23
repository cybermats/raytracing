#pragma once

#include <memory>

class Ray;
class Intersection;
class IShader;
class Scene;


class IShape {
public:
    virtual double intersect(const Ray &ray) const = 0;
    virtual void populate_intersection(Intersection &intersection) const = 0;
    virtual const IShader* shader() const = 0;
    virtual void initialize(const Scene& scene) = 0;
};