#pragma once

#include <memory>

class Ray;
class Intersection;
class IShader;


class IShape {
public:
    virtual double intersect(const Ray &ray) const = 0;
    virtual void populate_intersection(Intersection &intersection) const = 0;
    virtual IShader* material() const = 0;

};