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

namespace rt {
    TEST(Camera, initBasic) {
        Camera cam = Camera(Vector3(0, 0, -1), Vector2(1920, 1080));

        EXPECT_EQ(cam.getAxis()[0], Vector3(1, 0, 0));
        EXPECT_EQ(cam.getAxis()[1], Vector3(0, 1, 0));
        EXPECT_EQ(cam.getAxis()[2], Vector3(0, 0, -1));
        EXPECT_EQ(cam.getRes(), Vector2(1920, 1080));
    }

    TEST(Camera, initBasic2) {
        Camera cam = Camera(Vector3(-1, 0, 0), Vector2(1920, 1080));

        EXPECT_EQ(cam.getAxis()[0], Vector3(0, 0, -1));
        EXPECT_EQ(cam.getAxis()[1], Vector3(0, 1, 0));
        EXPECT_EQ(cam.getAxis()[2], Vector3(-1, 0, 0));
        EXPECT_EQ(cam.getRes(), Vector2(1920, 1080));
    }

    TEST(Camera, changingRes) {
        Camera cam = Camera(Vector3(-1, 0, 0), Vector2(1920, 1080));

        EXPECT_EQ(cam.getRes(), Vector2(1920, 1080));
        cam.setRes(Vector2(1080, 1080));
        EXPECT_EQ(cam.getRes(), Vector2(1080, 1080));
    }

    TEST(Camera, GenerateRayBasic) {
        Camera cam = Camera(Vector3(0, 0, -1), Vector2(1080, 1080));

        Vector3 ray = cam.GenerateRay(Vector2(0, 0));
        Vector3 cmp = Vector3(-1, 1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(540, 0));
        cmp = Vector3(0, 1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(1080, 0));
        cmp = Vector3(1, 1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(0, 540));
        cmp = Vector3(-1, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(540, 540));
        cmp = Vector3(0, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(1080, 540));
        cmp = Vector3(1, 0, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(0, 1080));
        cmp = Vector3(-1, -1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(540, 1080));
        cmp = Vector3(0, -1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
        ray = cam.GenerateRay(Vector2(1080, 1080));
        cmp = Vector3(1, -1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
    }

    TEST(Camera, GenerateRay) {
        Camera cam = Camera(Vector3(0, 1, 0), Vector3(0, 0, -1),
        Vector2(1080, 1080));

        Vector3 ray = cam.GenerateRay(Vector2(540, 540));
        Vector3 cmp = Vector3(0, -1, -1);
        cmp.Normalize();
        EXPECT_EQ(ray, cmp);
    }
}  // namespace rt
