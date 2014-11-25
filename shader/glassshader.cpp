#include "glassshader.h"



Color GlassShader::shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const {
    const Ray& ray = intersection.ray();
    if(ray.life())
    {
        const Vec3d& n = intersection.normal();
        const Vec3d& i = ray.direction();
        Vec3d r = reflect(i, n);

        double nq = _n1 / _n2;
        double cosI = dot(i, n);
        double sinT2 = nq * nq * ( 1 - cosI * cosI);
        if(sinT2 < 0)
            return Color::Red;

        Vec3d t = nq*i + (nq * cosI - sqrt(sinT2))*n;


        Ray reflectionRay(ray, intersection.point() + 0.000001 * t, t, ray.importance());
        secondaryRays.push_back(reflectionRay);
    }
    return Color::Black;
}

