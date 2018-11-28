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
#include "Vector2.h"

namespace rt {
    TEST(Vector2, initBasic) {
        Vector2 v = Vector2();

        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 0);
    }

    TEST(Vector2, initBasic2) {
        Vector2 v = Vector2(3, 4);

        EXPECT_EQ(v.GetX(), 3);
        EXPECT_EQ(v.GetY(), 4);
    }

    TEST(Vector2, setX) {
        Vector2 v = Vector2();

        v.SetX(3);
        EXPECT_EQ(v.GetX(), 3);
        EXPECT_EQ(v.GetY(), 0);
    }

    TEST(Vector2, setY) {
        Vector2 v = Vector2();

        v.SetY(4);
        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 4);
    }

    TEST(Vector2, operatorEgal) {
        Vector2 v = Vector2();
        Vector2 w = Vector2(1, 2);

        EXPECT_FALSE(v == w);
        v.SetX(1);
        v.SetY(2);
        EXPECT_TRUE(v == w);
    }

    TEST(Vector2, operatorNotEgal) {
        Vector2 v = Vector2();
        Vector2 w = Vector2(1, 2);

        EXPECT_TRUE(v != w);
        v.SetX(1);
        v.SetY(2);
        EXPECT_FALSE(v != w);
    }

    TEST(Vector2, operatorPlus) {
        Vector2 v = Vector2(1, 2);
        Vector2 w = Vector2(3, 4);

        EXPECT_EQ(v + w, Vector2(4, 6));
    }

    TEST(Vector2, operatorMinus) {
        Vector2 v = Vector2(1, 2);
        Vector2 w = Vector2(3, 4);

        EXPECT_EQ(v - w, Vector2(-2, -2));
    }

    TEST(Vector2, operatorMultiplication) {
        Vector2 v = Vector2(1, 2);

        EXPECT_EQ(v * 6, Vector2(6, 12));
    }
}  // namespace rt
