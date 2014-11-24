#pragma once

#include <cmath>
#include <memory>


template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

inline bool similar(double A, double B, int maxUlps = 10)
{
    static_assert(sizeof(double) == sizeof(long), "Int and double must be of same size.");

    long aInt = *(long*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x8000000000000000L - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    long bInt = *(long*)&B;
    if (bInt < 0)
        bInt = 0x8000000000000000L - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    long intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}
