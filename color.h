#pragma once

#include "vector.h"

#include <cassert>

struct Color
{
    static Color White;
    static Color Black;
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Teal;
    static Color Orange;

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
    return Color(c.r * v, c.g * v, c.b * v, c.a * v);
}

inline Color operator/(const Color& c, double v)
{
    return Color(c.r / v, c.g / v, c.b / v, c.a / v);
}

inline Color operator*(double v, const Color& c)
{
    return Color(c.r * v, c.g * v, c.b * v, c.a * v);
}

inline Color operator+(const Color& l, const Color& r)
{
    return Color(l.r + r.r, l.g + r.g, l.b + r.b, l.a + r.a);
}

inline Color operator*(const Color& l, const Color& r)
{
    return Color(l.r * r.r, l.g * r.g, l.b * r.b, l.a * r.a);
}

inline Color& operator+=(Color& l, const Color& r)
{
    l.r += r.r;
    l.g += r.g;
    l.b += r.b;
    l.a += r.a;
    return l;
}

inline bool operator==(const Color& l, const Color& r)
{
    return l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a;
}

inline bool operator!=(const Color& l, const Color& r)
{
    return !(l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a);
}