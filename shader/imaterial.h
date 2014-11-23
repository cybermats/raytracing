#pragma once

#include "../color.h"

class Intersection;

class IMaterial
{
public:
    virtual Color shade(const Intersection& intersection) const = 0;
};