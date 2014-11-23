#pragma once

#include "ishader.h"
#include "../intersection.h"
#include <vector>

class MirrorShader : public IShader
{

public:
    virtual Color shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const override;


    virtual void initialize() override {}
};

