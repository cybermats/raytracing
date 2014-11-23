#include "blinnshader.h"
#include "../scene.h"
#include "../vector.h"
#include "../vecmath.h"
#include "../color.h"


Color BlinnShader::shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const {
    Color output(0, 0, 0, 0);
    Color diffuseColor = _diffuseMaterial->shade(intersection);
    Color specularColor = _specularMaterial->shade(intersection);
    for(const auto& light : _scene->lights())
    {
        Color lightColor = light->shade(intersection.point());
        Vec3d lightDirection = light->direction(intersection.point());
        Vec3d normal = intersection.normal();
        Vec3d viewDirection = -intersection.ray().direction();
        Vec3d halfWay = normalize(lightDirection + viewDirection);

        double dDotN = dot(lightDirection, normal);
        if(dDotN > 0)
        {
            Color diffuseShading = diffuseColor * lightColor * _diffuse * dDotN;
            output += diffuseShading;
        }

        double hDotn = dot(halfWay, normal);
        if(hDotn > 0)
        {
            double dot = pow(hDotn, _alpha);
            Color specularShading = specularColor * lightColor * _specular * dot;
            output += specularShading;
        }
    }
    output.a = 1;
    return output;

}
