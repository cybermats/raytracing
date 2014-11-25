#pragma once

#include "ishader.h"
#include "../intersection.h"
#include <vector>

class GlassShader : public IShader
{
public:
    GlassShader(double n1, double n2) : _n1(n1), _n2(n2) {
    }

    virtual Color shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const override;


    virtual void initialize() override {}

private:
    double _n1;
    double _n2;
};