#pragma once

#include <memory>
#include <vector>
#include "igeometry.h"
#include "intersection.h"

class Scene
{
public:
    void add_shape(std::unique_ptr<IGeometry> shape)
    {
        _shapes.push_back(std::move(shape));
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


private:
    std::vector<std::unique_ptr<IGeometry>> _shapes;
};