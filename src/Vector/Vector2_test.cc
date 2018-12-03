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

#include <sstream>
#include <iostream>
#include "gtest/gtest.h"
#include "Vector2.h"

namespace rt {
    TEST(Vector2_int, initBasic) {
        Vector2<int> v = Vector2<int>();

        EXPECT_EQ(v.X, 0);
        EXPECT_EQ(v.Y, 0);
    }

    TEST(Vector2_int, initBasic2) {
        Vector2<int> v = Vector2<int>(3, 4);

        EXPECT_EQ(v.X, 3);
        EXPECT_EQ(v.Y, 4);
    }

    TEST(Vector2_int, setX) {
        Vector2<int> v = Vector2<int>();

        v.X = 3;
        EXPECT_EQ(v.X, 3);
        EXPECT_EQ(v.Y, 0);
    }

    TEST(Vector2_int, setY) {
        Vector2<int> v = Vector2<int>();

        v.Y = 4;
        EXPECT_EQ(v.X, 0);
        EXPECT_EQ(v.Y, 4);
    }

    TEST(Vector2_int, operatorEgal) {
        Vector2<int> v = Vector2<int>();
        Vector2<int> w = Vector2<int>(1, 2);

        EXPECT_FALSE(v == w);
        v.X = 1;
        v.Y = 2;
        EXPECT_TRUE(v == w);
    }

    TEST(Vector2_int, operatorNotEgal) {
        Vector2<int> v = Vector2<int>();
        Vector2<int> w = Vector2<int>(1, 2);

        EXPECT_TRUE(v != w);
        v.X = 1;
        v.Y = 2;
        EXPECT_FALSE(v != w);
    }

    TEST(Vector2_int, operatorPlus) {
        Vector2<int> v = Vector2<int>(1, 2);
        Vector2<int> w = Vector2<int>(3, 4);

        EXPECT_EQ(v + w, Vector2<int>(4, 6));
    }

    TEST(Vector2_int, operatorMinus) {
        Vector2<int> v = Vector2<int>(1, 2);
        Vector2<int> w = Vector2<int>(3, 4);

        EXPECT_EQ(v - w, Vector2<int>(-2, -2));
    }

    TEST(Vector2_int, operatorMultiplication) {
        Vector2<int> v = Vector2<int>(1, 2);

        EXPECT_EQ(v * 6, Vector2<int>(6, 12));
    }

    TEST(Vector2_int, operatorDivision) {
        Vector2<int> v = Vector2<int>(4, 2);

        EXPECT_EQ(v / 2, Vector2<int>(2, 1));
    }

    TEST(Vector2_int, Display) {
        Vector2<int> v = Vector2<int>(0, 1);
        std::stringstream ss1;

        ss1 << v;
        ASSERT_EQ(ss1.str(), "(0, 1)");
    }
}  // namespace rt
