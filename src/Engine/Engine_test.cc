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
#include "Engine.h"
#include "../Loader/AssimpLoader.h"
#include "../Camera/Camera.h"
#include "../Vector/Vector2.h"

namespace rt {/*
    TEST(Engine, raytraceEasy) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/icosahedron.obj")) {
            std::cerr << "Failed to load file. May have failed to "
                     "find it or it was not an .obj file." << std::endl;
            ASSERT_TRUE(false);
        }
        Engine engine = rt::Engine(loader, rt::Camera(rt::Vector3<float>(0, 0, 3),
                                                    rt::Vector3<float>(0, 0, -1),
                                                    rt::Vector2<unsigned int>(160, 90)));
        ASSERT_EQ(engine.raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0x00000000);
    }

    TEST(Engine, raytraceMedium) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/teapot.obj")) {
            std::cerr << "Failed to load file. May have failed to "
                     "find it or it was not an .obj file." << std::endl;
            ASSERT_TRUE(false);
        }
        Engine engine = rt::Engine(loader, rt::Camera(rt::Vector3<float>(0, 0, 120),
                                                    rt::Vector3<float>(0, 0, -1),
                                                    rt::Vector2<unsigned int>(160, 90)));
        ASSERT_EQ(engine.raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0x00000000);
    }*/
}  // namespace rt
