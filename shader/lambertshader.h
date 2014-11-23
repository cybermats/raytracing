#pragma once

#include "ishader.h"
#include "imaterial.h"
#include "../vector.h"
#include "../vecmath.h"
#include "../color.h"
#include "../intersection.h"
#include "../scene.h"


class LambertShader : public IShader
{
public:

    LambertShader(const Scene& scene, const std::string& colorName, double coefficient)
            : _scene(scene)
            , _colorName(colorName)
            , _coefficient(coefficient)
            , _material(nullptr)
    {}

    virtual Color shade(const Intersection &intersection, std::vector<Ray>& secondaryRays) const override;


    virtual void initialize() override;

private:
    const Scene& _scene;
    std::string _colorName;
    double _coefficient;

    const IMaterial* _material;
};

