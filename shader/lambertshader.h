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

    LambertShader(Scene* scene, IMaterial* material, double coefficient)
            : _scene(scene)
            , _material(material)
            , _coefficient(coefficient) {
    }

    virtual Color shade(const Intersection &intersection, std::vector<Ray>& secondaryRays) const override;


private:
    Scene* _scene;
    IMaterial* _material;
    double _coefficient;

};

