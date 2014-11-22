
#include "vector.h"
#include "vecmath.h"
#include "imagebuffer.h"
#include "imagewriter.h"
#include "camera.h"
#include "shape/sphere.h"
#include "scene.h"
#include "material/imaterial.h"
#include "material/lambertshader.h"
#include "pointlight.h"
#include "utils.h"

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
//    scene.add_light(make_unique<PointLight>(Vec3d(100, 0, -8), Color(1, 1, 1)));
    scene.add_light(make_unique<PointLight>(Vec3d(50, 50, 1), Color(98/255.0, 194/255.0, 204/255.0)));
    scene.add_light(make_unique<PointLight>(Vec3d(50, -50, 1), Color(253/255.0, 184/255.0, 19/255.0)));

    LambertShader lambert(&scene, Color(1, 1, 1, 1), 0.5);

    scene.add_shape(make_unique<Sphere>(Vec3d(-0.5, -0.5, -5), 1, &lambert));
    scene.add_shape(make_unique<Sphere>(Vec3d(0.5, 0.5, -5), 1, &lambert));

    for(auto& ray : rays)
    {
        auto intersection = scene.intersect(ray);
        if(!intersection)
            continue;
        Color c = intersection->shape()->material()->shade(*intersection);
        buffer->setPixel(c, intersection->ray().pixel());
    }


    ImageWriter writer(buffer);

    writer.savePNG("/Users/mats/foo.png");


    return 0;
}