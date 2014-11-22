#pragma once

#include "vector.h"
#include "vecmath.h"
#include "utils.h"
#include <cassert>

class Ray
{
public:
    Ray(Vec3d origin, Vec3d direction, Vec2i pixel, Vec3d dU, Vec3d dV)
            : _origin(std::move(origin))
            , _direction(std::move(direction))
            , _pixel(pixel)
            , _dU(dU)
            , _dV(dV)
    {
        assert(similar(length(_direction), 1.0));
    }

    Ray(Vec3d origin, Vec3d direction)
            : _origin(std::move(origin))
            , _direction(std::move(direction))
            , _pixel(0, 0)
            , _dU(0, 0, 0)
            , _dV(0, 0, 0)
    {
        assert(similar(length(_direction), 1.0));
    }

    const Vec3d& origin() const
    {
        return _origin;
    }

    const Vec3d& direction() const
    {
        return _direction;
    }

    const Vec2i& pixel() const {
        return _pixel;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Ray& r)
    {
        stream << "Ray(origin: " << r._origin << ", direction: " << r._direction << ", pixel: " << r._pixel << ")";
        return stream;
    }


private:
    Vec3d _origin;
    Vec3d _direction;

    Vec2i _pixel;
    Vec3d _dU;
    Vec3d _dV;

};