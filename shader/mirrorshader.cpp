#include "mirrorshader.h"
#include "../vecmath.h"


Color MirrorShader::shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const {
    const Ray& ray = intersection.ray();
    if(ray.life())
    {
        const Vec3d& n = intersection.normal();
        const Vec3d& d = ray.direction();
        Vec3d reflectionDir = reflect(d, n);
        Ray reflectionRay(ray, intersection.point() + 0.000001 * reflectionDir, reflectionDir);
        secondaryRays.push_back(reflectionRay);
    }
    return Color::Black;
}
