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
#include "PointLight.h"
#include "../Engine/Color.h"
#include "../Vector/Vector3.h"

namespace rt {
    TEST(PointLight, Init) {
        Color color = Color(0xff0000ff);
        PointLight light = PointLight(Vector3<float>(), color);

        EXPECT_EQ(light.GetPos(), Vector3<float>(0, 0, 0));
        EXPECT_EQ(light.GetBrightness(), 1.0f);
        EXPECT_EQ(light.GetColor().GetColor().hexcode, 0xff0000ff);

        PointLight light2 = PointLight(Vector3<float>(1, 2, 3));

        EXPECT_EQ(light2.GetPos(), Vector3<float>(1, 2, 3));
        EXPECT_EQ(light2.GetBrightness(), 1.0f);
        EXPECT_EQ(light2.GetColor().GetColor().hexcode, 0xffffffff);
    }
}  // namespace rt
