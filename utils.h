#pragma once

#include <cmath>
#include <memory>

#define SIMILAR(actual, expected) ( (abs(actual) - expected) < 1e-9)


template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}