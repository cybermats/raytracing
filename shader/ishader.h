#pragma once
#include "../color.h"

class Intersection;

class IShader
{
public:
    virtual Color shade(const Intersection& intersection) = 0;

};