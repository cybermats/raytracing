#pragma once

#include "ishader.h"
#include "imaterial.h"
#include "../intersection.h"

class Scene;

class PhongShader : public IShader
{
public:
    PhongShader(Scene *scene, IMaterial *diffuseMaterial, IMaterial *specularMaterial, double specular, double diffuse, double alpha)
            : _scene(scene),
              _diffuseMaterial(diffuseMaterial),
              _specularMaterial(specularMaterial),
              _specular(specular),
              _diffuse(diffuse),
              _alpha(alpha)
    {}

    virtual Color shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const override;
private:
    Scene* _scene;
    IMaterial* _diffuseMaterial;
    IMaterial* _specularMaterial;
    double _specular;
    double _diffuse;
    double _alpha;
};

