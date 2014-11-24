#pragma once

#include "ishader.h"
#include "imaterial.h"
#include "../intersection.h"

class Scene;

class BlinnShader : public IShader
{
public:
    BlinnShader(const Scene &scene, const std::string& diffuseMaterialName, const std::string& specularMaterialName,
            double diffuse, double specular, double alpha, double reflectiveness)
            : _scene(scene)
            , _diffuseMaterialName(diffuseMaterialName)
            , _specularMaterialName(specularMaterialName)
            , _diffuse(diffuse)
            , _specular(specular)
            , _alpha(alpha)
            , _reflectiveness(reflectiveness)
            , _diffuseMaterial(nullptr)
            , _specularMaterial(nullptr)
    {}

    virtual Color shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const override;


    virtual void initialize() override;

private:
    const Scene& _scene;
    std::string _diffuseMaterialName;
    std::string _specularMaterialName;
    double _diffuse;
    double _specular;
    double _alpha;
    double _reflectiveness;
    const IMaterial* _diffuseMaterial;
    const IMaterial* _specularMaterial;
};

