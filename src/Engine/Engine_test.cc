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

#include <SFML/Graphics.hpp>
#include "gtest/gtest.h"
#include "Engine.h"
#include "../Loader/AssimpLoader.h"
#include "../Camera/Camera.h"
#include "../Vector/Vector2.h"

namespace rt {
    TEST(Engine, Res) {
        AssimpLoader loader;
        Engine engine = rt::Engine(loader);
        ASSERT_EQ(engine.GetRes(), Vector2<unsigned int>(1600, 900));
    }

    TEST(Engine, raytraceEasy) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/Cube.dae")) {
            ASSERT_TRUE(false);
        }
        Engine engine = rt::Engine(loader);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0x00000000);
    }

    TEST(Engine, raytraceEasy2) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/Ico.dae")) {
            ASSERT_TRUE(false);
        }
        Engine engine = rt::Engine(loader);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0x00000000);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(800, 450)).GetColor().hexcode, 0x37373700);
    }

    TEST(Engine, raytraceHard) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/Dragon.dae")) {
            ASSERT_TRUE(false);
        }
        Engine engine = rt::Engine(loader);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0x00000000);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(800, 450)).GetColor().hexcode, 0x00000000);
    }

    TEST(Engine, raytraceHardcore) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/DragonOnStandDoubleLight.dae")) {
            ASSERT_TRUE(false);
        }
        Engine engine = rt::Engine(loader);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0xb390c00);
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(800, 450)).GetColor().hexcode, 0xf1f1f100);
    }

    TEST(Engine, raytraceWithBackground) {
        AssimpLoader loader;
        if (!loader.LoadFile("../scenes/Cube.dae")) {
            ASSERT_TRUE(false);
        }
        sf::Image skyTexture;
        skyTexture.loadFromFile("../scenes/sphereMap_joshua.jpg");
        Engine engine = rt::Engine(loader);
        engine.SetBackground(std::shared_ptr<Sky>(new rt::SphereSky(rt::Vector2<unsigned int>(skyTexture.getSize().x, skyTexture.getSize().y), skyTexture.getPixelsPtr())));
        ASSERT_EQ(engine.Raytrace(Vector2<unsigned int>(0, 0)).GetColor().hexcode, 0xc2baad00);
    }
}  // namespace rt
