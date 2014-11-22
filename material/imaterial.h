#pragma once
#include "../color.h"

class Intersection;

class IMaterial
{

    virtual Color shade(const Intersection& intersection) = 0;

};