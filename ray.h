#pragma once

#include "vector.h"
#include "vecmath.h"
#include "utils.h"
#include <cassert>

class Ray
{
public:
    Ray(Vec3d origin, Vec3d direction)
            : _origin(std::move(origin))
            , _direction(std::move(direction))
    {
        assert(SIMILAR(length(_direction), 1.0));
    }

    const Vec3d& origin() const
    {
        return _origin;
    }

    const Vec3d& direction() const
    {
        return _direction;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Ray& r)
    {
        stream << "Ray(origin: " << r._origin << ", direction: " << r._direction << ")";
        return stream;
    }


private:
    Vec3d _origin;
    Vec3d _direction;
};