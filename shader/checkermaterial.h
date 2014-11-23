#pragma once

#include "imaterial.h"
#include "../color.h"
#include "staticcolormaterial.h"

#include "../intersection.h"

class CheckerMaterial : public IMaterial
{
public:
    CheckerMaterial(IMaterial const &color1, IMaterial const &color2) : _color1(color1), _color2(color2) {
    }

    virtual Color shade(const Intersection &intersection) const override {
        Vec2d uv = intersection.uv();
        double uf = fmod(uv[0], 1);
        double vf = fmod(uv[1], 1);
        if(uf < 0)
            uf++;
        if(vf < 0)
            vf++;

        if(uf < 0.5 == vf < 0.5)
            return _color1.shade(intersection);
        else
            return _color2.shade(intersection);
    }

private:
    const IMaterial& _color1;
    const IMaterial& _color2;
};

