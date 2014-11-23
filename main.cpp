
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
#include "shader/mirrorshader.h"
#include "shader/checkermaterial.h"
#include "shader/staticcolormaterial.h"
#include "shader/phongshader.h"
#include "shader/blinnshader.h"

#include "supersampler.h"
#include "pointlight.h"
#include "utils.h"
#include <cmath>

#include <iostream>

int main()
{
    int width = 800;
    int height = 600;
    double fov = M_PI/4;
    double aspect = width/(double)height;
    Vec2i resolution(width, height);

    auto buffer = std::make_shared<ImageBuffer>(resolution);

    Vec3d camPos(-3, 3, 3);
    Vec3d camView(1, -1, -1);
    Vec3d camUp(0, 1, 0);

    Camera camera(camPos, camView, camUp, resolution, fov, aspect);
    SuperSampler sampler(1, true);
    auto camRays = camera.rays();
    auto primaryRays = sampler.generate(camRays);


    Scene scene;
//    scene.add_light(make_unique<PointLight>(Vec3d(100, 0, -8), Color(1, 1, 1)));
    scene.add_light(make_unique<PointLight>(&scene, Vec3d(50, 50, 0), Color::White));
//    scene.add_light(make_unique<PointLight>(&scene, Vec3d(-50, 50, -50), Color::Orange));


    StaticColorMaterial white(Color::White);
    StaticColorMaterial blue(Color::Blue);
    StaticColorMaterial red(Color::Red);
    StaticColorMaterial green(Color::Green);

    CheckerMaterial checkered(white, blue);

    LambertShader lambert(&scene, &checkered, 1);
    LambertShader lambertRed(&scene, &red, 1);
    LambertShader lambertGreen(&scene, &green, 1);
    LambertShader lambertBlue(&scene, &blue, 1);
    LambertShader lambertWhite(&scene, &white, 1);

    MirrorShader mirror;

    BlinnShader phongWhite(&scene, &white, &white, 0.5, 0.5, 100);


//    scene.add_shape(make_unique<Sphere>(Vec3d(-0.5, -0.5, -4), 1, &lambert));
//    scene.add_shape(make_unique<Sphere>(Vec3d(0.5, 0.5, -4), 1, &lambert));
    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, 0), 1, &mirror));
    scene.add_shape(make_unique<Sphere>(Vec3d(2, 0, 0), 1, &lambertRed));
    scene.add_shape(make_unique<Sphere>(Vec3d(-2, 0, 0), 1, &phongWhite));
    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, 2), 1, &lambertGreen));
    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, -2), 1, &lambertBlue));
    scene.add_shape(make_unique<Plane>(Vec3d(0, 1, 0), -1, &lambert));

    std::vector<Ray> secondaryRays(std::move(primaryRays));

    while(!secondaryRays.empty())
    {
        std::vector<Ray> rays(std::move(secondaryRays));
        for(auto& ray : rays)
        {
            auto intersection = scene.intersect(ray);
            if(!intersection)
                continue;
            Color c = intersection->shape()->material()->shade(*intersection, secondaryRays) * ray.importance();
            buffer->addPixel(c, intersection->ray().pixel());
        }
    }


    ImageWriter writer(buffer);

    writer.savePNG("/Users/mats/foo.png");


    return 0;
}