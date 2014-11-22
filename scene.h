#pragma once

#include "shape/igeometry.h"
#include "intersection.h"
#include "ilightsource.h"

#include <memory>
#include <vector>

class Scene
{
public:
    void add_shape(std::unique_ptr<IGeometry> shape)
    {
        _shapes.push_back(std::move(shape));
    }

    void add_light(std::unique_ptr<ILightSource> light)
    {
        _lights.push_back(std::move(light));
    }

    std::unique_ptr<Intersection> intersect(const Ray& ray) const
    {
        IGeometry* nearestHit = nullptr;
        double t_min = std::numeric_limits<double>::max();
        for(auto const& shape : _shapes)
        {
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

    bool hit(const Ray& ray, double length) const
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

    const std::vector<std::unique_ptr<ILightSource>>& lights() const
    {
        return _lights;
    }


private:
    std::vector<std::unique_ptr<IGeometry>> _shapes;
    std::vector<std::unique_ptr<ILightSource>> _lights;
};