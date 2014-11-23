#pragma once
#include "../color.h"

#include <vector>

class Intersection;
class Ray;

class IShader
{
public:
    virtual Color shade(const Intersection& intersection, std::vector<Ray>& secondaryRays) const = 0;
    virtual void initialize() = 0;
};