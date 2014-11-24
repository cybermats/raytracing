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

    Color(double cr, double cg, double cb)
            : r(cr)
            , g(cg)
            , b(cb)
            , a(1)
    {}

    Color(double cr, double cg, double cb, double ca)
            : r(cr)
            , g(cg)
            , b(cb)
            , a(ca)
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

inline std::ostream& operator<<(std::ostream& stream, const Color& c)
{
    stream << "Color(r: " << c.r
            << ", g: " << c.g
            << ", b: " << c.b
            << ", a: " << c.a
            << ")";
    return stream;
}

