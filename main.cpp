
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
#include "shader/filematerial.h"

#include "supersampler.h"
#include "pointlight.h"
#include "progresslog.h"
#include "utils.h"
#include <cmath>

#include <iostream>

void setupBox(Scene& scene);
void setupSpheres(Scene& scene);



int main()
{
    unsigned short width = 800;
    unsigned short height = 600;
    double fov = M_PI/2;
    double aspect = width/(double)height;
    Vec2us resolution(width, height);

    auto buffer = std::make_shared<ImageBuffer>(resolution);

    Vec3d camPos(0, 0, 1.95);
    Vec3d camView(0, 0, -1);
    Vec3d camUp(0, 1, 0);

    Camera camera(camPos, camView, camUp, resolution, fov, aspect);
    SuperSampler sampler(4, true);
    auto camRays = camera.rays();
    auto primaryRays = sampler.generate(camRays);
//    auto primaryRays = camRays;

    Scene scene;
//    setupSpheres(scene);
    setupBox(scene);

    std::cout << "Initializing" << std::endl;
    scene.initialize();

    std::vector<Ray> secondaryRays(std::move(primaryRays));

    int count = 1;
    while(!secondaryRays.empty())
    {
        std::cout << "Starting pass: " << count << ", size: " << secondaryRays.size() << std::endl;
        ProgressLog progress("Pass [" + std::to_string(count) + "]", 0, secondaryRays.size(), secondaryRays.size() / 10);
        std::vector<Ray> rays(std::move(secondaryRays));
        for(auto& ray : rays)
        {
            progress.progress();

            auto intersection = scene.intersect(ray);

            if(!intersection)
                continue;
            Color c = intersection->shape()->shader()->shade(*intersection, secondaryRays) * ray.importance();
            buffer->addPixel(c, intersection->ray().pixel());
        }
        std::cout << "Ending pass: " << count << std::endl;
        count++;
    }


    ImageWriter writer(buffer);
    std::cout << "Writing file" << std::endl;
    writer.savePNG("/Users/mats/Documents/raytracing/foo.png");


    return 0;
}

void setupBox(Scene& scene)
{
    scene.add_material("WhiteColor", make_unique<StaticColorMaterial>(Color::White));
    scene.add_material("BlueColor", make_unique<StaticColorMaterial>(Color::Blue));
    scene.add_material("RedColor", make_unique<StaticColorMaterial>(Color::Red));
    scene.add_material("GreenColor", make_unique<StaticColorMaterial>(Color::Green));

    scene.add_shader("LambertWhite", make_unique<LambertShader>(scene, "WhiteColor", 1));
    scene.add_shader("LambertRed", make_unique<LambertShader>(scene, "RedColor", 1));
    scene.add_shader("LambertBlue", make_unique<LambertShader>(scene, "BlueColor", 1));
    scene.add_shader("LambertGreen", make_unique<LambertShader>(scene, "GreenColor", 1));

    scene.add_shader("Mirror", make_unique<BlinnShader>(scene, "WhiteColor", "WhiteColor", 0.0, 0.0, 100, 1));

    scene.add_shape(make_unique<Plane>(Vec3d(0, 1, 0), -1, "LambertWhite"));
    scene.add_shape(make_unique<Plane>(Vec3d(0, -1, 0), -1, "LambertWhite"));
    scene.add_shape(make_unique<Plane>(Vec3d(1, 0, 0), -1, "LambertGreen"));
    scene.add_shape(make_unique<Plane>(Vec3d(-1, 0, 0), -1, "LambertRed"));
    scene.add_shape(make_unique<Plane>(Vec3d(0, 0, 1), -1, "LambertWhite"));
    scene.add_shape(make_unique<Plane>(Vec3d(0, 0, -1), -2, "LambertWhite"));

    scene.add_shape(make_unique<Sphere>(Vec3d(-0.4, -0.7, -0.4), 0.3, "Mirror"));
    scene.add_shape(make_unique<Sphere>(Vec3d(0.4, -0.7, 0.0), 0.3, "Mirror"));


    scene.add_light(make_unique<PointLight>(&scene, Vec3d(0, 0.95, 0), Color::White));

}

void setupSpheres(Scene& scene)
{
//    scene.add_light(make_unique<PointLight>(Vec3d(100, 0, -8), Color(1, 1, 1)));
    scene.add_light(make_unique<PointLight>(&scene, Vec3d(-50, 50, 50), Color::White));
    scene.add_light(make_unique<PointLight>(&scene, Vec3d(-50, 50, -50), Color::White));

    scene.add_material("WhiteColor", make_unique<StaticColorMaterial>(Color::White));
    scene.add_material("BlueColor", make_unique<StaticColorMaterial>(Color::Blue));
    scene.add_material("RedColor", make_unique<StaticColorMaterial>(Color::Red));
    scene.add_material("GreenColor", make_unique<StaticColorMaterial>(Color::Green));
    scene.add_material("WoodTexture", make_unique<FileMaterial>("/Users/mats/Documents/raytracing/woodtexture.png"));

    scene.add_material("Checker", make_unique<CheckerMaterial>("WhiteColor", "BlueColor"));

    scene.add_shader("Lambert", make_unique<LambertShader>(scene, "Checker", 1));
    scene.add_shader("LambertRed", make_unique<LambertShader>(scene, "RedColor", 1));
    scene.add_shader("LambertGreen", make_unique<LambertShader>(scene, "GreenColor", 1));
    scene.add_shader("LambertBlue", make_unique<LambertShader>(scene, "BlueColor", 1));
    scene.add_shader("LambertWhite", make_unique<LambertShader>(scene, "WhiteColor", 1));
    scene.add_shader("LambertWood", make_unique<LambertShader>(scene, "WoodTexture", 1));
//    scene.add_shader("Mirror", make_unique<MirrorShader>());
    scene.add_shader("Mirror", make_unique<BlinnShader>(scene, "WhiteColor", "WhiteColor", 0.5, 0.5, 100, 0.5));
    scene.add_shader("BlinnWhite", make_unique<BlinnShader>(scene, "WhiteColor", "WhiteColor", 0.5, 0.5, 100, 0));

    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, 0), 1, "Mirror"));
    scene.add_shape(make_unique<Sphere>(Vec3d(2, 0, 0), 1, "LambertRed"));
    scene.add_shape(make_unique<Sphere>(Vec3d(-2, 0, 0), 1, "Mirror"));
    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, 2), 1, "LambertWood"));
    scene.add_shape(make_unique<Sphere>(Vec3d(0, 0, -2), 1, "LambertBlue"));
    scene.add_shape(make_unique<Plane>(Vec3d(0, 1, 0), -1, "Mirror"));

}
