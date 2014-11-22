#pragma once

#include "vector.h"

#include <cassert>

struct Color
{
    Color() {}

    Color(double r, double g, double b)
            : r(r)
            , g(g)
            , b(b)
            , a(1)
    {}

    Color(double r, double g, double b, double a)
            : r(r)
            , g(g)
            , b(b)
            , a(a)
    {}

    Color(const Vec3d& vec)
            : r(vec.x)
            , g(vec.y)
            , b(vec.z)
            , a(1)
    {}

    double operator[](size_t idx) const
    {
        assert(idx < 4);
        switch (idx)
        {
            case 0:
                return r;
            case 1:
                return g;
            case 2:
                return b;
            case 3:
                return a;
            default:
                return a;
        }
    }


    double r;
    double g;
    double b;
    double a;
};

inline Color operator*(const Color& c, double v)
{
    return Color(c.r * v, c.g * v, c.b * v, c.a);
}

inline Color operator*(double v, const Color& c)
{
    return Color(c.r * v, c.g * v, c.b * v, c.a);
}

inline Color operator+(const Color& l, const Color& r)
{
    return Color(l.r + r.r, l.g + r.g, l.b + r.g, l.a * r.a);
}