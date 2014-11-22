#pragma once

#include "imaterial.h"
#include "../vector.h"
#include "../vecmath.h"
#include "../color.h"
#include "../intersection.h"
#include "../scene.h"


class LambertShader : public IMaterial
{
public:

    LambertShader(Scene* scene, Color color, double coefficient)
            : _scene(scene)
            , _color(color)
            , _coefficient(coefficient) {
    }

    virtual Color shade(const Intersection &intersection) override {
        Color output(0, 0, 0, 1);
        for(const auto& light : _scene->lights())
        {
            Vec3d lightDir = light->direction(intersection.point());
            Ray ray(intersection.point() + 0.00000001 * lightDir, lightDir);

            if(_scene->hit(ray, 10))
                continue;



            Color lightColor = light->color();
            Vec3d direction = normalize(light->direction(intersection.point()));
            Color shadeColor = lightColor * _coefficient * std::max(0.0, dot(direction, intersection.normal()));
            output = output + shadeColor;
        }
        return output;
    }

private:
    Scene* _scene;
    Color _color;
    double _coefficient;

};

