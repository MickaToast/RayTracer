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
#include "SphereSky.h"

namespace rt {
    TEST(SphereSky, uniformSphereColor) {
        std::uint8_t pixels[4] = {0x42, 0x42, 0x42, 0x00};
        SphereSky sky(Vector2<unsigned int>(1, 1), pixels);

        ASSERT_EQ(sky.GetPixel(Vector3<float>(0, 0, 0)).GetColor().hexcode, 0x42424200);
    }

    TEST(SphereSky, verticalyUniformSphereColor) {
        std::uint8_t pixels[8] = {0x42, 0x42, 0x42, 0x00, 0x24, 0x24, 0x24, 0x00};
        SphereSky sky(Vector2<unsigned int>(1, 2), pixels);

        ASSERT_EQ(sky.GetPixel(Vector3<float>(0, 0, 1)).GetColor().hexcode, 0x42424200);
        ASSERT_EQ(sky.GetPixel(Vector3<float>(0, 0, -1)).GetColor().hexcode, 0x24242400);
    }
}  // namespace rt
