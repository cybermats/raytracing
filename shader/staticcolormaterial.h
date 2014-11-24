#pragma once

#include "imaterial.h"
#include "../color.h"
#include "../intersection.h"

class Intersection;

class StaticColorMaterial : public IMaterial
{

public:
    StaticColorMaterial(Color color) : _color(std::move(color)) {}
    virtual ~StaticColorMaterial();

    virtual Color shade(const Intersection &) const override {
        return _color;
    }


    virtual void initialize(const Scene &) override {}

private:
    Color _color;
};
