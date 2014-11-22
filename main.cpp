
#include "vector.h"
#include "vecmath.h"
#include "imagebuffer.h"
#include "imagewriter.h"
#include "camera.h"
#include "shape/sphere.h"
#include "shape/plane.h"
#include "scene.h"
#include "shader/ishader.h"
#include "shader/lambertshader.h"
#include "pointlight.h"
#include "utils.h"

int main()
{
    int width = 800;
    int height = 600;
    double fov = 3.14/4;
    double aspect = width/(double)height;
    Vec2i resolution(width, height);


    auto buffer = std::make_shared<ImageBuffer>(resolution);

    Vec3d camPos(0, 0, 1);
    Vec3d camView(0, 0, -1);
    Vec3d camUp(0, 1, 0);

    Camera camera(camPos, camView, camUp, resolution, fov, aspect);
    auto rays = camera.rays();


    Scene scene;
//    scene.add_light(make_unique<PointLight>(Vec3d(100, 0, -8), Color(1, 1, 1)));
    scene.add_light(make_unique<PointLight>(&scene, Vec3d(50, 50, 1), Color::Teal));
    scene.add_light(make_unique<PointLight>(&scene, Vec3d(50, -50, 1), Color::Orange));

    LambertShader lambert(&scene, Color::White, 0.5);

//    scene.add_shape(make_unique<Sphere>(Vec3d(-0.5, -0.5, -4), 1, &lambert));
//    scene.add_shape(make_unique<Sphere>(Vec3d(0.5, 0.5, -4), 1, &lambert));
    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, -4), 1, &lambert));
    scene.add_shape(make_unique<Plane>(Vec3d(0, 1, 0), -1, &lambert));

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