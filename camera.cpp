#include "camera.h"

Camera::Camera(Vec3d position, Vec3d view, const Vec3d& up, Vec2i resolution, double fov, double aspect)
: _position(std::move(position))
, _u(cross(view, up))
, _v(cross(_u, view))
, _w(std::move(view))
, _resolution(resolution)
, _fov(fov)
, _aspect(aspect)
, _dX(2 * tan(_fov/2)/_resolution.x)
, _dY(2 * tan((_fov/_aspect)/2)/_resolution.y)
{}

std::vector<Ray> Camera::rays() const
{
    Vec3d scanlineStart = _position +
            _w -
            (_resolution.x/2) * _dX * _u +
            (_resolution.y/2) * _dY * _v +
            (_dX/2) * _u -
            (_dY/2) * _v;


    std::vector<Ray> rays;
    rays.reserve(_resolution.x * _resolution.y);

    Vec3d dU = _dX * _u;
    Vec3d dV = _dY * _v;
    Vec2i pixel(0, 0);

    for(int y = 0; y < _resolution.y; ++y)
    {
        Vec3d pixelCenter = scanlineStart;

        for(int x = 0; x < _resolution.x; ++x)
        {
            Ray ray(_position, normalize(pixelCenter), pixel, dU, dV);
            rays.push_back(ray);

            pixelCenter += dU;
            pixel.x++;
        }
        scanlineStart -= dV;
        pixel.y++;
        pixel.x = 0;
    }
    return rays;
}
