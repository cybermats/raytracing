#include <gtest/gtest.h>
#include "vector.h"
#include "vecmath.h"
#include "ray.h"
#include "intersection.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



TEST(Vector, Construction)
{
    Vec3d v(1, 2, 3);
    Vec3d w;

    w = v;

    EXPECT_EQ(1, w.x);
    EXPECT_EQ(2, w.y);
    EXPECT_EQ(3, w.z);

    EXPECT_EQ(1, w[0]);
    EXPECT_EQ(2, w[1]);
    EXPECT_EQ(3, w[2]);

    EXPECT_EQ(w, v);

    w.x = 4;
    EXPECT_EQ(4, w.x);
    EXPECT_EQ(4, w[0]);
}

TEST(Vector, CompoundAssignment)
{
    Vec3d v(1, 0, 0);
    Vec3d w(0, 1, 0);

    v += w;
    EXPECT_EQ(Vec3d(1, 1, 0), v);

    v -= w;
    EXPECT_EQ(Vec3d(1, 0, 0), v);

    w *= 2;
    EXPECT_EQ(Vec3d(0, 2, 0), w);


}

TEST(Vector, Operands)
{
    Vec3d v(1, 0, 0);
    Vec3d w(0, 1, 0);
    Vec3d l(3, 4, 5);

    EXPECT_EQ(Vec3d(1, 1, 0), v + w);
    EXPECT_EQ(Vec3d(1, -1, 0), v - w);
    EXPECT_EQ(Vec3d(2, 0, 0), v * 2);
    EXPECT_EQ(Vec3d(2, 0, 0), 2 * v);

    EXPECT_EQ(sqrt(50), length(l));
    EXPECT_EQ(50, length2(l));

    EXPECT_EQ(3, dot(v, l));
}

TEST(Vector, CrossProduct)
{
    Vec3d a(1, 0, 0);
    Vec3d b(0, 1, 0);

    EXPECT_EQ(Vec3d(0, 0, 1), cross(a, b));
    EXPECT_EQ(0, dot(a, cross(a, b)));
    EXPECT_EQ(0, dot(b, cross(a, b)));
}

TEST(Intersection, Basic)
{
    Vec3d origin(0, 0, 0);
    Vec3d dir(1, 0, 0);

    Ray ray(origin, dir);

    double t = 2.0;

    Intersection inter(ray, t);

    EXPECT_EQ(origin, inter.ray().origin());
    EXPECT_EQ(dir, inter.ray().direction());
    EXPECT_EQ(Vec3d(2, 0, 0), inter.point());
}

TEST(Sphere, Basic)
{
    Vec3d origin(0, 0, 0);
    Vec3d dir(1, 0, 0);


    Vec3d sphereOrigin(2, 0, 0);
    double sphereRadius = 1;

    Sphere sphere(sphereOrigin, sphereRadius);

    Ray ray(origin, dir);
    EXPECT_EQ(1, sphere.intersect(ray));
    Intersection inter(ray, 1);
    sphere.populate_intersection(inter);
    EXPECT_EQ(Vec3d(1, 0, 0), inter.point());
    EXPECT_EQ(Vec3d(-1, 0, 0), inter.normal());

    Ray ray2(Vec3d(0, 1, 0), Vec3d(1, 0, 0));
    EXPECT_EQ(2, sphere.intersect(ray2));
    Intersection inter2(ray2, 2);
    sphere.populate_intersection(inter2);
    EXPECT_EQ(Vec3d(2, 1, 0), inter2.point());
    EXPECT_EQ(Vec3d(0, 1, 0), inter2.normal());

    Ray ray3(Vec3d(0, 2, 0), Vec3d(1, 0, 0));
    EXPECT_EQ(-1, sphere.intersect(ray3));
}

TEST(Scene, Basic)
{
    Scene scene;
    Vec3d origin(0, 0, 0);
    Vec3d dir(1, 0, 0);
    Ray ray(origin, dir);
    auto intersection = scene.intersect(ray);
    EXPECT_FALSE((bool)intersection);

    auto sphere = new Sphere(Vec3d(4, 0, 0), 1);
    scene.add_shape(std::unique_ptr<IGeometry>(sphere));
    intersection = scene.intersect(ray);
    EXPECT_TRUE((bool)intersection);

    auto sphere2 = new Sphere(Vec3d(-4, 0, 0), 1);
    scene.add_shape(std::unique_ptr<IGeometry>(sphere2));
    intersection = scene.intersect(ray);
    EXPECT_TRUE((bool)intersection);
    EXPECT_EQ(sphere, intersection->shape());
}