#include "lambertshader.h"

Color LambertShader::shade(const Intersection &intersection, std::vector<Ray>& secondaryRays) const {
    Color output(0, 0, 0, 0);
    Color materialColor = _material->shade(intersection);
    for(const auto& light : _scene->lights())
    {
        Color lightColor = light->shade(intersection.point());
        Vec3d direction = light->direction(intersection.point());
        Color shadeColor = materialColor * lightColor * _coefficient * std::max(0.0, dot(direction, intersection.normal()));
        output = output + shadeColor;
    }
    output.a = 1.0;
    return output;
}
