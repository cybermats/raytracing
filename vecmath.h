#pragma once

#include "vector.h"
#include <math.h>

template<std::size_t Dim, class T>
Vec<Dim, T> operator+(const Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    std::array<T, Dim> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = l[i] + r[i];
    return Vec<Dim, T>(std::move(temp));
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator-(const Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    std::array<T, Dim> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = l[i] - r[i];
    return Vec<Dim, T>(std::move(temp));
}


template<std::size_t Dim, class T>
Vec<Dim, T>& operator+=(Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    for(std::size_t i = 0; i < Dim; ++i)
        l[i] += r[i];
    return l;
}

template<std::size_t Dim, class T>
Vec<Dim, T>& operator-=(Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    for(std::size_t i = 0; i < Dim; ++i)
        l[i] -= r[i];
    return l;
}


template<std::size_t Dim, class T>
Vec<Dim, T> operator*(const Vec<Dim, T>& v, double d)
{
    std::array<T, Dim> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = v[i] * d;
    return Vec<Dim, T>(std::move(temp));
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator*(double d, const Vec<Dim, T>& v)
{
    std::array<T, Dim> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = v[i] * d;
    return Vec<Dim, T>(std::move(temp));
}

template<std::size_t Dim, class T>
Vec<Dim, T>& operator*=(Vec<Dim, T>& v, double d)
{
    for(std::size_t i = 0; i < Dim; ++i)
        v[i] *= d;
    return v;
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator/(const Vec<Dim, T>& v, double d)
{
    std::array<T, Dim> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = v[i] / d;
    return Vec<Dim, T>(std::move(temp));
}

template<std::size_t Dim, class T>
Vec<Dim, T>& operator/=(Vec<Dim, T>& v, double d)
{
    for(std::size_t i = 0; i < Dim; ++i)
        v[i] /= d;
    return v;
}


template<std::size_t Dim, class T>
inline T length(const Vec<Dim, T>& v)
{
    return sqrt(length2(v));
}

template<std::size_t Dim, class T>
inline T length2(const Vec<Dim, T>& v)
{
    T len = 0;
    for(std::size_t i = 0; i < Dim; ++i)
        len += v[i]*v[i];
    return len;
}

template<std::size_t Dim, class T>
T dot(const Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    T len = 0;
    for(std::size_t i = 0; i < Dim; ++i)
        len += l[i]*r[i];
    return len;
}

template<class T>
Vec<3, T> cross(const Vec<3, T>& a, const Vec<3, T>& b)
{
    return Vec<3, T>(
            a.y*b[2] - a[2]*b[1],
            a[2]*b[0] - a[0]*b[2],
            a[0]*b[1] - a[1]*b[0]);
}

template<std::size_t Dim, class T>
Vec<Dim, T> normalize(const Vec<Dim, T>& v)
{
    T len = length(v);
    return v / len;
}

