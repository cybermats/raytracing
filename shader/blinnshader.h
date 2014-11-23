#pragma once

#include "ishader.h"
#include "imaterial.h"
#include "../intersection.h"

class Scene;

class BlinnShader : public IShader
{
public:
    BlinnShader(Scene *scene, IMaterial *diffuseMaterial, IMaterial *specularMaterial, double diffuse, double specular, double alpha)
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
    double _diffuse;
    double _specular;
    double _alpha;
};

