#include "phongshader.h"
#include "../scene.h"
#include "../vector.h"
#include "../vecmath.h"
#include "../color.h"


Color PhongShader::shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const {
    assert(_diffuseMaterial);
    assert(_specularMaterial);

    Color output(0, 0, 0, 0);
    Color diffuseColor = _diffuseMaterial->shade(intersection);
    Color specularColor = _specularMaterial->shade(intersection);
    for(const auto& light : _scene->lights())
    {
        Color lightColor = light->shade(intersection.point());
        Vec3d lightDirection = light->direction(intersection.point());
        Vec3d normal = intersection.normal();
        Vec3d lightReflection = reflect(-lightDirection, normal);
        Vec3d viewDirection = -intersection.ray().direction();

        double dDotN = dot(lightDirection, intersection.normal());
        if(dDotN > 0)
        {
            Color diffuseShading = diffuseColor * lightColor * _diffuse * dDotN;
            output += diffuseShading;
        }

        double rDotD = dot(lightReflection, viewDirection);
        if(rDotD > 0)
        {
            double dot = pow(rDotD, _alpha);
            Color specularShading = specularColor * lightColor * _specular * dot;
            output += specularShading;
        }
    }
    output.a = 1;
    return output;

}
