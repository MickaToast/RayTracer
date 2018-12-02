/* Copyright (c) 2018 mickael.leclerc@epitech.eu charles.fraisse@epitech.eu
 Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE. */

#include "gtest/gtest.h"
#include "Triangle.h"
#include "../Camera/Camera.h"

namespace rt {
    TEST(Triangle, initBasic) {
        Triangle t = Triangle(
            Vector3<float>(),
            Vector3<float>(1, 1, 1),
            Vector3<float>(2, 2, 2)
            );

        EXPECT_EQ(t.GetEdge1(), Vector3<float>(1, 1, 1));
        EXPECT_EQ(t.GetEdge2(), Vector3<float>(2, 2, 2));
    }

    TEST(Triangle, initBasic2) {
        Triangle t = Triangle(
            Vector3<float>(),
            Vector3<float>(1, 1, 1),
            Vector3<float>(2, 2, 2),
            objl::Material()
            );

        EXPECT_EQ(t.GetEdge1(), Vector3<float>(1, 1, 1));
        EXPECT_EQ(t.GetEdge2(), Vector3<float>(2, 2, 2));
    }

    TEST(Triangle, Intersection) {
        Camera cam = Camera(Vector3<float>(0, 0, 0), Vector3<float>(0, 0, -1), Vector2<int>(1920, 1080));
        Triangle t = Triangle(
            Vector3<float>(1, -1, -1),
            Vector3<float>(1, 1, -1),
            Vector3<float>(-1, -1, -1)
            );

        Intersection inter = t.Intersect(cam.GenerateRay(Vector2<int>(960, 540)));
        EXPECT_TRUE(inter.Intersect);
        EXPECT_EQ(Vector3<float>(0, 0, -1), inter.Point);
        inter = t.Intersect(cam.GenerateRay(Vector2<int>(0, 0)));
        EXPECT_FALSE(inter.Intersect);
    }

    TEST(Triangle, Refraction) {
        Triangle t = Triangle(
            Vector3<float>(),
            Vector3<float>(1, 1, 1),
            Vector3<float>(2, 2, 2)
            );
        t.Refract(Ray()); //TODO
    }

    TEST(Triangle, Reflection) {
        Triangle t = Triangle(
            Vector3<float>(),
            Vector3<float>(1, 1, 1),
            Vector3<float>(2, 2, 2)
            );
        t.Reflect(Ray()); //TODO
    }
}  // namespace rt
