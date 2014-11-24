#pragma once

#include "vector.h"
#include "vecmath.h"
#include "color.h"
#include "utils.h"
#include <cassert>

class Ray
{
public:
    Ray(Vec3d origin, Vec3d direction, Vec2us pixel, Vec3d dU, Vec3d dV, Color importance)
            : _origin(std::move(origin))
            , _direction(std::move(direction))
            , _pixel(pixel)
            , _life(4)
            , _dU(dU)
            , _dV(dV)
            , _importance(importance)
    {
        assert(similar(length(_direction), 1.0));
    }

    Ray(Vec3d origin, Vec3d direction)
            : _origin(std::move(origin))
            , _direction(std::move(direction))
            , _pixel(0, 0)
            , _life(4)
            , _dU(0, 0, 0)
            , _dV(0, 0, 0)
            , _importance(Color::White)
    {
        assert(similar(length(_direction), 1.0));
    }

    Ray(const Ray& original, Vec3d origin, Vec3d direction, Color importance)
            : _origin(std::move(origin))
            , _direction(std::move(direction))
            , _pixel(original._pixel)
            , _life(original._life - 1)
            , _dU(original._dU)
            , _dV(original._dV)
            , _importance(importance)
    {}


    const inline Vec3d& origin() const
    {
        return _origin;
    }

    const inline Vec3d& direction() const
    {
        return _direction;
    }

    const inline Vec2us& pixel() const {
        return _pixel;
    }

    unsigned int inline life() const {
        return _life;
    }

    const Color& importance() const {
        return _importance;
    }


    const Vec3d &dU() const {
        return _dU;
    }

    const Vec3d &dV() const {
        return _dV;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Ray& r)
    {
        stream << "Ray(origin: " << r._origin
                << ", direction: " << r._direction
                << ", pixel: " << r._pixel
                << ", life: " << r._life
                << ", dU: " << r._dU
                << ", dV: " << r._dV
                << ", importance: " << r._importance
                << ")";
        return stream;
    }


private:
    Vec3d _origin;
    Vec3d _direction;

    Vec2us _pixel;
    unsigned int _life;
    Vec3d _dU;
    Vec3d _dV;

    Color _importance;
};
