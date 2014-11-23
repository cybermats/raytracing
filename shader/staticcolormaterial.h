#pragma once

#include "imaterial.h"
#include "../color.h"
#include "../intersection.h"

class Intersection;

class StaticColorMaterial : public IMaterial
{

public:
    StaticColorMaterial(Color color) : _color(std::move(color)) {}

    virtual Color shade(const Intersection &intersection) const override {
        return _color;
    }

private:
    Color _color;
};

