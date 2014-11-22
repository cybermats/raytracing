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