#include "blinnshader.h"
#include "../scene.h"
#include "../vector.h"
#include "../vecmath.h"
#include "../color.h"


Color BlinnShader::shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const {
    assert(_diffuseMaterial);
    assert(_specularMaterial);
    Color output(0, 0, 0, 0);
    Color diffuseColor = _diffuseMaterial->shade(intersection);
    Color specularColor = _specularMaterial->shade(intersection);

    const Ray& ray = intersection.ray();
    const Vec3d& point = intersection.point();
    const Vec3d& normal = intersection.normal();
    Vec3d viewDirection = -ray.direction();
    const Vec3d& direction = ray.direction();

    if(_reflectiveness < 1)
    {
        for(const auto& light : _scene.lights())
        {
            Color lightColor = light->shade(point);
            Vec3d lightDirection = light->direction(point);
            Vec3d halfWay = normalize(lightDirection + viewDirection);

            double dDotN = dot(lightDirection, normal);
            if(dDotN > 0)
            {
                Color diffuseShading = diffuseColor * lightColor * _diffuse * dDotN;
                output += diffuseShading * (1 - _reflectiveness);
            }

            double hDotn = dot(halfWay, normal);
            if(hDotn > 0)
            {
                double dot = pow(hDotn, _alpha);
                Color specularShading = specularColor * lightColor * _specular * dot;
                output += specularShading * (1 - _reflectiveness);
            }
        }
    }
    if(_reflectiveness > 0)
    {
        if(intersection.ray().life())
        {
            Vec3d reflectionDir = reflect(direction, normal);
            Ray reflectionRay(ray, point + 0.000001 * reflectionDir, reflectionDir, ray.importance() * _reflectiveness);
            secondaryRays.push_back(reflectionRay);
        }
    }
    output.a = 1;
    return output;

}

void BlinnShader::initialize() {
    _diffuseMaterial = _scene.get_material(_diffuseMaterialName);
    _specularMaterial = _scene.get_material(_specularMaterialName);


}
