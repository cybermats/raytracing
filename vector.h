#pragma once

#include <cassert>
#include <ostream>

template<class T>
struct Vec3
{
    Vec3() {}

    Vec3(T x, T y, T z)
            : x(x), y(y), z(z)
    {}

    T& operator[](size_t idx)
    {
        assert(idx < 3);
        switch(idx) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    }

    T operator[](size_t idx) const
    {
        assert(idx < 3);
        switch(idx) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
            default:
                return z;
        }
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vec3& v)
    {
        stream << "Vec<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ", " << v.z << ")";
        return stream;
    }

    T x;
    T y;
    T z;
};


using Vec3d = Vec3<double>;