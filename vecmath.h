#pragma once

#include "vector.h"
#include "utils.h"
#include <math.h>

template<std::size_t Dim, class T>
Vec<Dim, T> operator+(const Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    Vec<Dim, T> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = l[i] + r[i];
    return temp;
}

template<class T>
Vec<3, T> operator+(const Vec<3, T>& l, const Vec<3, T>& r)
{
    return Vec<3, T>(l.x + r.x, l.y + r.y, l.z + r.z);
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator-(const Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    Vec<Dim, T> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = l[i] - r[i];
    return temp;
}

template<class T>
Vec<3, T> operator-(const Vec<3, T>& l, const Vec<3, T>& r)
{
    return Vec<3, T>(l.x - r.x, l.y - r.y, l.z - r.z);
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator-(const Vec<Dim, T>& v)
{
    Vec<Dim, T> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = -v[i];
    return temp;
}

template<class T>
Vec<3, T> operator-(const Vec<3, T>& v)
{
    return Vec<3, T>(-v.x, -v.y, -v.z);
}


template<std::size_t Dim, class T>
Vec<Dim, T>& operator+=(Vec<Dim, T>& l, const Vec<Dim, T>& r)
{
    for(std::size_t i = 0; i < Dim; ++i)
        l[i] += r[i];
    return l;
}

template<class T>
Vec<3, T>& operator+=(Vec<3, T>& l, const Vec<3, T>& r)
{
    l.x += r.x;
    l.y += r.y;
    l.z += r.z;
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
Vec<3, T>& operator-=(Vec<3, T>& l, const Vec<3, T>& r)
{
    l.x -= r.x;
    l.y -= r.y;
    l.z -= r.z;
    return l;
}


template<std::size_t Dim, class T>
Vec<Dim, T> operator*(const Vec<Dim, T>& v, double d)
{
    Vec<Dim, T> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = v[i] * d;
    return temp;
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator*(double d, const Vec<Dim, T>& v)
{
    Vec<Dim, T> temp;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = v[i] * d;
    return temp;
}

template<class T>
Vec<3, T> operator*(const Vec<3, T>& v, double d)
{
    return Vec<3, T>(v.x * d, v.y * d, v.z * d);
}

template<class T>
Vec<3, T> operator*(double d, const Vec<3, T>& v)
{
    return Vec<3, T>(v.x * d, v.y * d, v.z * d);
}

template<std::size_t Dim, class T>
Vec<Dim, T>& operator*=(Vec<Dim, T>& v, double d)
{
    for(std::size_t i = 0; i < Dim; ++i)
        v[i] *= d;
    return v;
}

template<class T>
Vec<3, T>& operator*=(Vec<3, T>& v, double d)
{
    v.x *= d;
    v.y *= d;
    v.z *= d;
    return v;
}

template<std::size_t Dim, class T>
Vec<Dim, T> operator/(const Vec<Dim, T>& v, double d)
{
    Vec<Dim, T> temp;
    double id = 1/d;
    for(std::size_t i = 0; i < Dim; ++i)
        temp[i] = v[i] * id;
    return temp;
}

template<class T>
Vec<3, T> operator/(const Vec<3, T>& v, double d)
{
    double id = 1/d;
    return Vec<3, T>(v.x * id, v.y * id, v.z * id);
}

template<std::size_t Dim, class T>
Vec<Dim, T>& operator/=(Vec<Dim, T>& v, double d)
{
    for(std::size_t i = 0; i < Dim; ++i)
        v[i] /= d;
    return v;
}

template<class T>
Vec<3, T>& operator/=(Vec<3, T>& v, double d)
{
    double id = 1 / d;
    v.x *= id;
    v.y *= id;
    v.z *= id;
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

template<class T>
inline T length2(const Vec<3, T>& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
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
T dot(const Vec<3, T>& l, const Vec<3, T>& r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

template<class T>
Vec<3, T> cross(const Vec<3, T>& a, const Vec<3, T>& b)
{
    return Vec<3, T>(
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x);
}

template<std::size_t Dim, class T>
inline Vec<Dim, T> normalize(const Vec<Dim, T>& v)
{
    T len = length(v);
    return v / len;
}

template<class T>
inline Vec<3, T> reflect(const Vec<3, T>& v, const Vec<3, T>& n)
{
    return v - 2 * dot(n, v) * n;
}

template<std::size_t Dim>
bool similar(const Vec<Dim, double>& a, const Vec<Dim, double>& b)
{
    for(std::size_t i = 0; i < Dim; ++i)
    {
        if(!similar(a[i], b[i]))
            return false;
    }
    return true;
}

template<std::size_t Dim, class T>
bool operator==(const Vec<Dim, T>& a, const Vec<Dim, T>& b)
{
    for(std::size_t i = 0; i < Dim; ++i)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}

template<std::size_t Dim>
bool operator==(const Vec<Dim, double>& a, const Vec<Dim, double>& b)
{
    for(std::size_t i = 0; i < Dim; ++i)
    {
        if(!similar(a[i], b[i]))
            return false;
    }
    return true;
}

template<std::size_t Dim, class T>
bool operator!=(const Vec<Dim, T>& a, const Vec<Dim, T>& b)
{
    for(std::size_t i = 0; i < Dim; ++i)
    {
        if(a[i] == b[i])
            return false;
    }
    return true;
}

template<std::size_t Dim>
bool operator!=(const Vec<Dim, double>& a, const Vec<Dim, double>& b)
{
    for(std::size_t i = 0; i < Dim; ++i)
    {
        if(similar(a[i], b[i]))
            return false;
    }
    return true;
}

