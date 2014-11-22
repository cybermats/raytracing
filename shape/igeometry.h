#pragma once

#include <memory>

class Ray;
class Intersection;
class IMaterial;


class IGeometry {
public:
    virtual double intersect(const Ray &ray) const = 0;
    virtual void populate_intersection(Intersection &intersection) const = 0;
    virtual IMaterial* material() const = 0;

};