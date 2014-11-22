#pragma once

class Ray;
class Intersection;


class IGeometry {
public:
    virtual double intersect(const Ray &ray) = 0;

    virtual void populate_intersection(Intersection &intersection) = 0;
};