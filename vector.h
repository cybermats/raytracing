#pragma once

#include <cassert>
#include <ostream>
#include <array>

namespace {
    template<std::size_t Dim, class T>
    std::ostream& operator<<(std::ostream& os, const std::array<T, Dim>& arr) {
        copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(os, " "));
        return os;
    }
}

template<std::size_t Dim, class T>
class Vec
{
public:
    Vec(){}

    template <typename... Tail>
    Vec(typename std::enable_if<sizeof...(Tail)+1 == Dim, T>::type head, Tail... tail)
            : _a{ head, T(tail)... }
    {}

    Vec(std::array<T, Dim>&& arr)
            : _a(std::move(arr))
    {}

    T& operator[](size_t idx) {
        assert(idx < Dim);
        return _a[idx];
    }

    const T& operator[](size_t idx) const {
        assert(idx < Dim);
        return _a[idx];
    }

    bool operator==(const Vec& other) const {
        return _a == other._a;
    }

    bool operator!=(const Vec& other) const {
        return _a != other._a;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Vec &v) {
        stream << "Vec<" << typeid(T).name() << ">(" << v._a << ")";
        return stream;
    }


private:
    std::array<T, Dim> _a;
};

template<class T>
class Vec<3, T>
{
public:
    Vec()
    {}

    Vec(T vx, T vy, T vz)
            : x(vx)
            , y(vy)
            , z(vz)
    {}

    T& operator[](size_t idx) {
        assert(idx < 3);
        switch (idx)
        {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    }

    const T& operator[](size_t idx) const {
        assert(idx < 3);
        switch (idx)
        {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    }

    friend std::ostream &operator<<(std::ostream &stream, const Vec &v) {
        stream << "Vec<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ", "  << v.z << ")";
        return stream;
    }

    T x;
    T y;
    T z;
};


template<class T>
class Vec<2, T>
{
public:
    Vec()
    {}

    Vec(T vx, T vy)
            : x(vx)
            , y(vy)
    {}

    inline T& operator[](size_t idx) {
        assert(idx < 2);
        switch (idx)
        {
            case 0:
                return x;
            case 1:
            default:
                return y;
        }
    }

    const inline T& operator[](size_t idx) const {
        assert(idx < 2);
        switch (idx)
        {
            case 0:
                return x;
            case 1:
            default:
                return y;
        }
    }

    friend std::ostream &operator<<(std::ostream &stream, const Vec &v) {
        stream << "Vec<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ")";
        return stream;
    }

    T x;
    T y;

};


using Vec3d = Vec<3, double>;
using Vec2i = Vec<2, int>;
using Vec2us = Vec<2, unsigned short>;
using Vec2ul = Vec<2, unsigned long>;
using Vec2d = Vec<2, double>;
