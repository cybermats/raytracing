#pragma once

#include "vector.h"
#include <math.h>

template<class T>
Vec3<T> operator+(const Vec3<T>& l, const Vec3<T>& r)
{
    return Vec3<T>(l.x + r.x, l.y + r.y, l.z + r.z);
}

template<class T>
Vec3<T> operator-(const Vec3<T>& l, const Vec3<T>& r)
{
    return Vec3<T>(l.x - r.x, l.y - r.y, l.z - r.z);
}

template<class T>
Vec3<T> operator*(const Vec3<T>& v, double d)
{
    return Vec3<T>(v.x * d, v.y * d, v.z * d);
}

template<class T>
Vec3<T> operator*(double d, const Vec3<T>& v)
{
    return Vec3<T>(v.x * d, v.y * d, v.z * d);
}


template<class T>
T length(const Vec3<T>& v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

template<class T>
T length2(const Vec3<T>& v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

template<class T>
T dot(const Vec3<T>& l, const Vec3<T>& r)
{
    return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
}

