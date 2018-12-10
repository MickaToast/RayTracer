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
#include "Color.h"

namespace rt {
    TEST(Color, initBasic) {
        Color color(0x00000000);

        ASSERT_EQ(color.GetColor().rgba.r, 0);
        ASSERT_EQ(color.GetColor().rgba.g, 0);
        ASSERT_EQ(color.GetColor().rgba.b, 0);
        ASSERT_EQ(color.GetColor().rgba.a, 0);
    }

    TEST(Color, initComponent) {
        Color_Component component;
        component.hexcode = 0x00000000;
        Color color(component);

        ASSERT_EQ(color.GetColor().rgba.r, 0);
        ASSERT_EQ(color.GetColor().rgba.g, 0);
        ASSERT_EQ(color.GetColor().rgba.b, 0);
        ASSERT_EQ(color.GetColor().rgba.a, 0);
    }

    TEST(Color, red) {
        Color color(0xff000000);

        ASSERT_EQ(color.GetColor().rgba.r, 0xff);
        ASSERT_EQ(color.GetColor().rgba.g, 0);
        ASSERT_EQ(color.GetColor().rgba.b, 0);
        ASSERT_EQ(color.GetColor().rgba.a, 0);
    }

    TEST(Color, green) {
        Color color(0x00ff0000);

        ASSERT_EQ(color.GetColor().rgba.r, 0);
        ASSERT_EQ(color.GetColor().rgba.g, 0xff);
        ASSERT_EQ(color.GetColor().rgba.b, 0);
        ASSERT_EQ(color.GetColor().rgba.a, 0);
    }

    TEST(Color, blue) {
        Color color(0x0000ff00);

        ASSERT_EQ(color.GetColor().rgba.r, 0);
        ASSERT_EQ(color.GetColor().rgba.g, 0);
        ASSERT_EQ(color.GetColor().rgba.b, 0xff);
        ASSERT_EQ(color.GetColor().rgba.a, 0);
    }

    TEST(Color, alpha) {
        Color color(0x000000ff);

        ASSERT_EQ(color.GetColor().rgba.r, 0);
        ASSERT_EQ(color.GetColor().rgba.g, 0);
        ASSERT_EQ(color.GetColor().rgba.b, 0);
        ASSERT_EQ(color.GetColor().rgba.a, 0xff);
    }

    TEST(Color, setColor) {
        Color color(0x000000ff);
        Color_Component component;

        component.hexcode = 0xffffffff;
        color.SetColor(component);
        ASSERT_EQ(color.GetColor().rgba.r, 0xff);
        ASSERT_EQ(color.GetColor().rgba.g, 0xff);
        ASSERT_EQ(color.GetColor().rgba.b, 0xff);
        ASSERT_EQ(color.GetColor().rgba.a, 0xff);
    }

    TEST(Color, Add) {
        Color color(0x0f0f0fff);
        color += Color(0x123456ff);
        
        ASSERT_EQ(color.GetColor().hexcode, 0x214365ff);
    }
}  // namespace rt
