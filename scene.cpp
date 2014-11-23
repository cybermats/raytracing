#include "scene.h"

bool Scene::hit(const Ray& ray, double length) const
{
    double t_min = std::numeric_limits<double>::max();
    for(auto const& shape : _shapes)
    {
        double t = shape->intersect(ray);
        if(t < 0)
            continue;
        if(t > t_min)
            continue;
        t_min = t;
    }
    return t_min < length;
}


std::unique_ptr<Intersection> Scene::intersect(const Ray& ray) const
{
    IShape* nearestHit = nullptr;
    double t_min = std::numeric_limits<double>::max();
    for(auto const& shape : _shapes)
    {
        assert(shape);
        double t = shape->intersect(ray);
        if(t < 0)
            continue;
        if(t > t_min)
            continue;
        t_min = t;
        nearestHit = shape.get();
    }

    if(nearestHit)
    {
        auto inter = new Intersection(ray, t_min);
        nearestHit->populate_intersection(*inter);
        return std::unique_ptr<Intersection>(inter);
    }
    return nullptr;
}
