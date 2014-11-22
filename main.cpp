
#include "vector.h"
#include "vecmath.h"
#include "imagebuffer.h"
#include "imagewriter.h"
#include "camera.h"
#include "shape/sphere.h"
#include "scene.h"
#include "material/imaterial.h"

#include <string>

int main()
{
    int width = 320;
    int height = 240;
    double fov = 3.14/4;
    double aspect = width/(double)height;
    Vec2i resolution(width, height);


    auto buffer = std::make_shared<ImageBuffer>(resolution);

    Vec3d camPos(0, 0, 0);
    Vec3d camView(0, 0, -1);
    Vec3d camUp(0, 1, 0);

    Camera camera(camPos, camView, camUp, resolution, fov, aspect);
    auto rays = camera.rays();

    Scene scene;
    scene.add_shape(std::unique_ptr<IGeometry>(new Sphere(Vec3d(0, 0, -4), 1)));
    scene.add_shape(std::unique_ptr<IGeometry>(new Sphere(Vec3d(1, 1, -4), 1)));

    for(auto& ray : rays)
    {
        auto intersection = scene.intersect(ray);
        if(!intersection)
            continue;
        buffer->setPixel(intersection->normal(), intersection->ray().pixel());
    }


    ImageWriter writer(buffer);

    writer.savePNG("/Users/mats/foo.png");


    return 0;
}