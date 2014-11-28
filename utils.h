#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>


template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#ifdef WIN32
#define ConvLong long long
#else
#define ConvLong long
#endif

inline bool similar(double A, double B, int maxUlps = 10)
{
	static_assert(sizeof(double) == sizeof(ConvLong), "Int and double must be of same size.");

	ConvLong aInt = *(ConvLong*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x8000000000000000L - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
	ConvLong bInt = *(ConvLong*)&B;
    if (bInt < 0)
        bInt = 0x8000000000000000L - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
	ConvLong intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}
