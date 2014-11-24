#pragma once

#include "vector.h"
#include "vecmath.h"
#include "ray.h"
#include <vector>

class Camera
{
public:
    Camera(Vec3d position, const Vec3d& view, const Vec3d& up, Vec2us resolution, double fov, double aspect);

    std::vector<Ray> rays() const;

private:
    Vec3d _position;

    Vec3d _u;
    Vec3d _v; // "Up"
    Vec3d _w; // View direction

    Vec2us _resolution;

    double _fov;
    double _aspect;
    double _dX;
    double _dY;

};
