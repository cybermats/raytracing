#pragma once

#include "imaterial.h"
#include "../color.h"
#include "staticcolormaterial.h"

#include "../intersection.h"
#include "../scene.h"

class CheckerMaterial : public IMaterial
{
public:
    CheckerMaterial(std::string const &color1Name, std::string const &color2Name)
            : _color1Name(color1Name)
            , _color2Name(color2Name)
            , _color1(nullptr)
            , _color2(nullptr)
    {}
    virtual ~CheckerMaterial();

    virtual Color shade(const Intersection &intersection) const override {
        Vec2d uv = intersection.uv();
        double uf = fmod(uv[0], 1);
        double vf = fmod(uv[1], 1);
        if(uf < 0)
            uf++;
        if(vf < 0)
            vf++;

        if(uf < 0.5 == vf < 0.5)
            return _color1->shade(intersection);
        else
            return _color2->shade(intersection);
    }

    virtual void initialize(const Scene &scene) override
    {
        _color1 = scene.get_material(_color1Name);
        _color2 = scene.get_material(_color2Name);
    }


private:
    std::string _color1Name;
    std::string _color2Name;

    const IMaterial* _color1;
    const IMaterial* _color2;
};

