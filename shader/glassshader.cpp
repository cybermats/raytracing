#include "glassshader.h"

double reflectance(const Vec3d& normal, const Vec3d& incident, double n1, double n2)
{
	const double nq = n1 / n2;
	const double cosI = -dot(normal, incident);
	const double sinT2 = nq * nq * (1 - cosI * cosI);
	if (sinT2 > 1) return 1.0;
	const double cosT = sqrt(1 - sinT2);
	const double rOrth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	const double rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
	return (rOrth * rOrth + rPar * rPar) / 2;
}

Color GlassShader::shade(const Intersection &intersection, std::vector<Ray> &secondaryRays) const {
    const Ray& ray = intersection.ray();
    if(ray.life())
    {
        const Vec3d& n = intersection.normal();
        const Vec3d& i = ray.direction();
        Vec3d r = reflect(i, n);

		int sign = 1;
        double nq = _n1 / _n2;
        double cosI = -dot(i, n);
		if (cosI < 0)
		{
			cosI = -cosI;
			nq = 1 / nq;
			sign = -1;
		}

        double sinT2 = nq * nq * ( 1 - cosI * cosI);
        if(sinT2 > 1)
            return Color::Red;
		double cosT = sqrt(1 - sinT2);

        Vec3d t = nq*i + (sign * (nq * cosI - cosT))*n;

		double ref = reflectance(n, i, _n1, _n2);
		double tra = 1 - ref;
		if (ref > 0)
			secondaryRays.push_back(Ray(ray, intersection.point() + 0.000001 * r, r, ray.importance() * ref));
		if (tra > 0)
			secondaryRays.push_back(Ray(ray, intersection.point() + 0.000001 * t, t, ray.importance() * tra));

    }
    return Color::Black;
}

