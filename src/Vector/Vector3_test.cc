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

#include <cmath>
#include "gtest/gtest.h"
#include "Vector3.h"

namespace rt {
    TEST(Vector3, initBasic) {
        Vector3<float> v = Vector3<float>();

        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 0);
        EXPECT_EQ(v.GetZ(), 0);
    }

    TEST(Vector3, initBasic2) {
        Vector3<float> v = Vector3<float>(3, 4, 5);

        EXPECT_EQ(v.GetX(), 3);
        EXPECT_EQ(v.GetY(), 4);
        EXPECT_EQ(v.GetZ(), 5);
    }

    TEST(Vector3, setX) {
        Vector3<float> v = Vector3<float>();

        v.SetX(3);
        EXPECT_EQ(v.GetX(), 3);
        EXPECT_EQ(v.GetY(), 0);
        EXPECT_EQ(v.GetZ(), 0);
    }

    TEST(Vector3, setY) {
        Vector3<float> v = Vector3<float>();

        v.SetY(4);
        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 4);
        EXPECT_EQ(v.GetZ(), 0);
    }

    TEST(Vector3, setZ) {
        Vector3<float> v = Vector3<float>();

        v.SetZ(5);
        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 0);
        EXPECT_EQ(v.GetZ(), 5);
    }

    TEST(Vector3, operatorEgal) {
        Vector3<float> v = Vector3<float>();
        Vector3<float> w = Vector3<float>(1, 2, 3);

        EXPECT_FALSE(v == w);
        v.SetX(1);
        v.SetY(2);
        v.SetZ(3);
        EXPECT_TRUE(v == w);
    }

    TEST(Vector3, operatorNotEgal) {
        Vector3<float> v = Vector3<float>();
        Vector3<float> w = Vector3<float>(1, 2, 3);

        EXPECT_TRUE(v != w);
        v.SetX(1);
        v.SetY(2);
        v.SetZ(3);
        EXPECT_FALSE(v != w);
    }

    TEST(Vector3, operatorPlus) {
        Vector3<float> v = Vector3<float>(1, 2, 3);
        Vector3<float> w = Vector3<float>(4, 5, 6);

        EXPECT_EQ(v + w, Vector3<float>(5, 7, 9));
    }

    TEST(Vector3, operatorMinus) {
        Vector3<float> v = Vector3<float>(1, 2, 3);
        Vector3<float> w = Vector3<float>(4, 5, 6);

        EXPECT_EQ(v - w, Vector3<float>(-3, -3, -3));
    }

    TEST(Vector3, operatorMultiplication) {
        Vector3<float> v = Vector3<float>(1, 2, 3);

        EXPECT_EQ(v * 6, Vector3<float>(6, 12, 18));
    }

    TEST(Vector3, operatorDivision) {
        Vector3<float> v = Vector3<float>(1, 2, 3);

        EXPECT_EQ(v / 2, Vector3<float>(0.5, 1, 1.5));
    }

    TEST(Vector3, CrossProduct) {
        Vector3<float> v = Vector3<float>(1, 2, 3);
        Vector3<float> w = Vector3<float>(4, 5, 6);

        EXPECT_EQ(v.Cross(w), Vector3<float>(-3, 6, -3));
    }

    TEST(Vector3, DotProduct) {
        Vector3<float> v = Vector3<float>(1, 2, 3);
        Vector3<float> w = Vector3<float>(4, 5, 6);

        EXPECT_EQ(v.Dot(w), 32);
    }

    TEST(Vector3, Norm) {
        Vector3<float> v = Vector3<float>(2, 3, 2);

        ASSERT_NEAR(v.Norm(), std::sqrt(17), 0.0000001);
    }

    TEST(Vector3, Normalize) {
        Vector3<float> v = Vector3<float>(2, 3, 2);

        ASSERT_NEAR(v.Norm(), std::sqrt(17), 0.0000001);
        v.Normalize();
        ASSERT_EQ(v.Norm(), 1);
    }
}  // namespace rt
