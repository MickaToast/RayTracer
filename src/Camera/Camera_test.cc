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
#include "Camera.h"
#include "../Engine/Tools.h"

namespace rt {
    TEST(Camera, initBasic) {
        Camera cam = Camera();

        EXPECT_EQ(cam. GetRes(), Vector2<unsigned int>(1600, 900));
        EXPECT_EQ(cam. GetPos(), Vector3<float>(0, 0, 0));
    }

    TEST(Camera, GenerateRay) {
        Camera cam = Camera();

        Ray ray = cam.GenerateRay(Vector2<unsigned int>(800, 450));
        Vector3<float> cmp = Vector3<float>(0, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
    }

    TEST(Camera, GenerateRayFHD) {
        Camera cam = Camera();

        Ray ray = cam.GenerateRay(Vector2<unsigned int>(0, 0));
        Vector3<float> cmp = Vector3<float>(-1, 0.5625, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(800, 0));
        cmp = Vector3<float>(0, 0.5625, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(1600, 0));
        cmp = Vector3<float>(1, 0.5625, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(0, 450));
        cmp = Vector3<float>(-1, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(800, 450));
        cmp = Vector3<float>(0, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(1600, 450));
        cmp = Vector3<float>(1, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(0, 900));
        cmp = Vector3<float>(-1, -0.5625, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(800, 900));
        cmp = Vector3<float>(0, -0.5625, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
        ray = cam.GenerateRay(Vector2<unsigned int>(1600, 900));
        cmp = Vector3<float>(1, -0.5625, -1);
        cmp.Normalize();
        EXPECT_EQ(ray.Direction, cmp);
    }
}  // namespace rt
