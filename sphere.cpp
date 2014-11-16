double Sphere::intersect(const Ray &ray) {

    Vec3d o = ray.origin();
    Vec3d d = ray.direction();

    const double a = 1;
    double b = 2 * (d.x *(o.x - _origin.x) + d.y * (o.y - _origin.y) + d.z * (o.z - _origin.z));
    double c = (o.x - _origin.x) * (o.x - _origin.x) +
            (o.y - _origin.y) * (o.y - _origin.y) +
            (o.z - _origin.z) * (o.z - _origin.z) -
            _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0.0)
        return -1;

    double inv_disc = sqrt(discriminant);
    double t = (-b - inv_disc) / 2 * a;

    if(t > 0)
        return t;
    t = (-b + inv_disc) / 2 * a;
    return t;
}

void Sphere::populate_intersection(Intersection &intersection) {
    double inv_radius = 1 / _radius;
    intersection.normal((intersection.point() - _origin) * inv_radius);
}
