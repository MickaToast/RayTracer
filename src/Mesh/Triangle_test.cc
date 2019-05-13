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
#include "Triangle.h"
#include "../Camera/Camera.h"

namespace rt {
    TEST(Triangle, initBasic) {
        Triangle t = Triangle(
                Vector3<float>(),
                Vector3<float>(1, 1, 1),
                Vector3<float>(2, 2, 2)
        );

        EXPECT_EQ(t.GetEdge1(), Vector3<float>(1, 1, 1));
        EXPECT_EQ(t.GetEdge2(), Vector3<float>(2, 2, 2));
        EXPECT_EQ(t.GetV1(), Vector3<float>());
        EXPECT_EQ(t.GetV2(), Vector3<float>(1, 1, 1));
        EXPECT_EQ(t.GetV3(), Vector3<float>(2, 2, 2));
    }

    TEST(Triangle, initBasic2) {
        Triangle t = Triangle(
                Vector3<float>(),
                Vector3<float>(1, 1, 1),
                Vector3<float>(2, 2, 2),
                Material()
        );

        EXPECT_EQ(t.GetEdge1(), Vector3<float>(1, 1, 1));
        EXPECT_EQ(t.GetEdge2(), Vector3<float>(2, 2, 2));
    }

    TEST(Triangle, Intersection) {
        Triangle t2 = Triangle(
                Vector3<float>(),
                Vector3<float>(1, 0, 0),
                Vector3<float>(0, 1, 0)
        );
        EXPECT_TRUE(t2.Intersect(Ray(
                Vector3<float>(.3, .3, 1),
                Vector3<float>(0, 0, -1)
        )).Intersect);
        EXPECT_FALSE(t2.Intersect(Ray(
                Vector3<float>(.3, .3, 1),
                Vector3<float>(0, 0, 1)
        )).Intersect);
        t2 = Triangle(
                Vector3<float>(),
                Vector3<float>(0, 1, 0),
                Vector3<float>(1, 0, 0)
        );
        EXPECT_TRUE(t2.Intersect(Ray(
                Vector3<float>(.3, .3, 1),
                Vector3<float>(0, 0, -1)
        )).Intersect);

        Triangle t3 = Triangle(
                Vector3<float>(0, 0, -1),
                Vector3<float>(3, 0, -1),
                Vector3<float>(0, 0, 0)
        );
        EXPECT_FALSE(t3.Intersect(Ray(
                Vector3<float>(1.5, 3, -0.5),
                Vector3<float>(0, 1, 0)
        )).Intersect);
    }

    TEST(Triangle, MaterialRetrieving) {
        Triangle t = Triangle(
                Vector3<float>(),
                Vector3<float>(1, 1, 1),
                Vector3<float>(2, 2, 2)
        );
        Material mat = t.GetMaterial();
        EXPECT_EQ(mat.Kd, Vector3<float>(0, 1, 0));
    }

    TEST(Triangle, GetNormal) {
        Triangle t = Triangle(
                Vector3<float>(),
                Vector3<float>(0, 0, -1),
                Vector3<float>(1, 0, 0)
        );
        EXPECT_EQ(t.GetNormal(), Vector3<float>(0, -1, 0));
    }

    TEST(Triangle, GetMinMax) {
        Triangle t = Triangle(
                Vector3<float>(1, 4, -5),
                Vector3<float>(5, -3, 2),
                Vector3<float>(2, 3, -8)
        );
        EXPECT_EQ(t.GetMinMaxX(), Vector2<float>(1, 5));
        EXPECT_EQ(t.GetMinMaxY(), Vector2<float>(-3, 4));
        EXPECT_EQ(t.GetMinMaxZ(), Vector2<float>(-8, 2));
    }

    TEST(Triangle, GetMidPoint) {
        Triangle t = Triangle(
                Vector3<float>(1, 4, -5),
                Vector3<float>(5, -3, 2),
                Vector3<float>(2, 3, -8)
        );
        EXPECT_EQ(t.GetMidPoint(), Vector3<float>(3, .5, -3));
    }

    TEST(Triangle, EqualOperator) {
        Triangle t = Triangle(
                Vector3<float>(1, 4, -5),
                Vector3<float>(5, -3, 2),
                Vector3<float>(2, 3, -8)
        );
        Triangle t2 = Triangle(
                Vector3<float>(1, 4, -5),
                Vector3<float>(5, -3, 2),
                Vector3<float>(2, 3, -8)
        );
        EXPECT_TRUE(t == t2);
    }
}  // namespace rt
