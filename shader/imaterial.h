#pragma once

#include "../color.h"

class Intersection;
class Scene;

class IMaterial
{
public:
    virtual ~IMaterial();
    virtual Color shade(const Intersection& intersection) const = 0;
    virtual void initialize(const Scene& scene) = 0;
};
