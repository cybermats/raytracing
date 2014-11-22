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
            : _a()
            , x(_a[0])
            , y(_a[1])
            , z(_a[2])
    {}

    Vec(T x, T y, T z)
            : _a{x, y, z}
            , x(_a[0])
            , y(_a[1])
            , z(_a[2])
    {}

    Vec(std::array<T, 3>&& arr)
            : _a(std::move(arr))
            , x(_a[0])
            , y(_a[1])
            , z(_a[2])
    {}

    Vec(const Vec& other)
            : _a(other._a)
            , x(_a[0])
            , y(_a[1])
            , z(_a[2])
    {}

    Vec& operator=(Vec other)
    {
        _a = std::move(other._a);
        x = _a[0];
        y = _a[1];
        z = _a[2];
        return *this;
    }

    T& operator[](size_t idx) {
        assert(idx < 3);
        return _a[idx];
    }

    const T& operator[](size_t idx) const {
        assert(idx < 3);
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

    T& x;
    T& y;
    T& z;

private:
    std::array<T, 3> _a;
};


template<class T>
class Vec<2, T>
{
public:
    Vec()
            : _a()
            , x(_a[0])
            , y(_a[1])
    {}

    Vec(T x, T y)
            : _a{x, y}
            , x(_a[0])
            , y(_a[1])
    {}

    Vec(std::array<T, 2>&& arr)
            : _a(std::move(arr))
            , x(_a[0])
            , y(_a[1])
    {}

    Vec(const Vec& other)
            : _a(other._a)
            , x(_a[0])
            , y(_a[1])
    {}

    Vec& operator=(Vec other)
    {
        _a = std::move(other._a);
        x = _a[0];
        y = _a[1];
        return *this;
    }

    T& operator[](size_t idx) {
        assert(idx < 2);
        return _a[idx];
    }

    const T& operator[](size_t idx) const {
        assert(idx < 2);
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

    T& x;
    T& y;

private:
    std::array<T, 2> _a;
};


using Vec3d = Vec<3, double>;
using Vec2i = Vec<2, int>;
using Vec2d = Vec<2, double>;
