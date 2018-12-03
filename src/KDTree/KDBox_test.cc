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
#include "KDBox.h"

namespace rt {
    void feedVector(std::vector<Triangle> &triangles) {
        triangles.push_back(
            Triangle(
                Vector3<float>(0, 0.5, -0.5),
                Vector3<float>(1.5, 0.5, 0),
                Vector3<float>(1.5, 0, -0.5)
            )
        );
        triangles.push_back(
            Triangle(
                Vector3<float>(3, 0.5, -0.5),
                Vector3<float>(1.5, 0.5, -1),
                Vector3<float>(1.5, 1, -0.5)
            )
        );
    }

    TEST(KDBox, MinMax) {
        std::vector<Triangle> triangles;
        feedVector(triangles);
        KDBox box = KDBox(triangles);
        EXPECT_EQ(box.GetX(), Vector2<float>(0, 3));
        EXPECT_EQ(box.GetY(), Vector2<float>(0, 1));
        EXPECT_EQ(box.GetZ(), Vector2<float>(-1, 0));
    }

    TEST(KDBox, LongestAxisX) {
        std::vector<Triangle> triangles;
        feedVector(triangles);
        KDBox box = KDBox(triangles);
        EXPECT_EQ(box.GetLongestAxis(), 0);
    }

    TEST(KDBox, LongestAxisY) {
        std::vector<Triangle> triangles;
        triangles.push_back(
            Triangle(
                Vector3<float>(0, 7.5, -0.5),
                Vector3<float>(1.5, 0.5, 0),
                Vector3<float>(1.5, 0, -0.5)
            )
        );
        triangles.push_back(
            Triangle(
                Vector3<float>(3, 0.5, -0.5),
                Vector3<float>(1.5, -0.5, -1),
                Vector3<float>(1.5, 1, -0.5)
            )
        );
        KDBox box = KDBox(triangles);
        EXPECT_EQ(box.GetLongestAxis(), 1);
    }

    TEST(KDBox, LongestAxisZ) {
        std::vector<Triangle> triangles;
        triangles.push_back(
            Triangle(
                Vector3<float>(0, 3.5, -10.5),
                Vector3<float>(1.5, 0.5, 0),
                Vector3<float>(1.5, 0, -0.5)
            )
        );
        triangles.push_back(
            Triangle(
                Vector3<float>(3, 0.5, -0.5),
                Vector3<float>(1.5, -0.5, -1),
                Vector3<float>(1.5, 1, 20.5)
            )
        );
        KDBox box = KDBox(triangles);
        EXPECT_EQ(box.GetLongestAxis(), 2);
    }

    TEST(KDBox, Triangles) {
        std::vector<Triangle> triangles;
        feedVector(triangles);
        KDBox box = KDBox(triangles);
        std::vector<Triangle> boxTriangles = box.GetTriangles();
        EXPECT_EQ(boxTriangles.size(), 12);
        EXPECT_EQ(boxTriangles[0], Triangle(
            Vector3<float>(0, 0, -1),
            Vector3<float>(3, 0, -1),
            Vector3<float>(0, 0, 0)
        ));
        EXPECT_EQ(boxTriangles[1], Triangle(
            Vector3<float>(0, 0, 0),
            Vector3<float>(3, 0, -1),
            Vector3<float>(3, 0, 0)
        ));
        EXPECT_EQ(boxTriangles[2], Triangle(
            Vector3<float>(0, 0, 0),
            Vector3<float>(3, 0, 0),
            Vector3<float>(0, 1, 0)
        ));
        EXPECT_EQ(boxTriangles[3], Triangle(
            Vector3<float>(0, 1, 0),
            Vector3<float>(3, 0, 0),
            Vector3<float>(3, 1, 0)
        ));
        EXPECT_EQ(boxTriangles[4], Triangle(
            Vector3<float>(0, 1, 0),
            Vector3<float>(3, 1, 0),
            Vector3<float>(0, 1, -1)
        ));
        EXPECT_EQ(boxTriangles[5], Triangle(
            Vector3<float>(0, 1, -1),
            Vector3<float>(3, 1, 0),
            Vector3<float>(3, 1, -1)
        ));
        EXPECT_EQ(boxTriangles[6], Triangle(
            Vector3<float>(0, 1, -1),
            Vector3<float>(3, 1, -1),
            Vector3<float>(0, 0, -1)
        ));
        EXPECT_EQ(boxTriangles[7], Triangle(
            Vector3<float>(0, 0, -1),
            Vector3<float>(3, 1, -1),
            Vector3<float>(3, 0, -1)
        ));
        EXPECT_EQ(boxTriangles[8], Triangle(
            Vector3<float>(0, 0, -1),
            Vector3<float>(0, 0, 0),
            Vector3<float>(0, 1, -1)
        ));
        EXPECT_EQ(boxTriangles[9], Triangle(
            Vector3<float>(0, 1, -1),
            Vector3<float>(0, 0, 0),
            Vector3<float>(0, 1, 0)
        ));
        EXPECT_EQ(boxTriangles[10], Triangle(
            Vector3<float>(3, 0, 0),
            Vector3<float>(3, 0, -1),
            Vector3<float>(3, 1, 0)
        ));
        EXPECT_EQ(boxTriangles[11], Triangle(
            Vector3<float>(3, 1, 0),
            Vector3<float>(3, 0, -1),
            Vector3<float>(3, 1, -1)
        ));
    }

    TEST(KDBox, Intersection) {
        std::vector<Triangle> triangles;
        feedVector(triangles);
        KDBox box = KDBox(triangles);

        EXPECT_TRUE(box.Intersect(Ray(
            Vector3<float>(1.5, 0.5, 3),
            Vector3<float>(0, 0, -1)
        )));
        EXPECT_TRUE(box.Intersect(Ray(
            Vector3<float>(1.5, 0.5, -3),
            Vector3<float>(0, 0, 1)
        )));
        EXPECT_TRUE(box.Intersect(Ray(
            Vector3<float>(5, 0.5, -0.5),
            Vector3<float>(-1, 0, 0)
        )));
        EXPECT_TRUE(box.Intersect(Ray(
            Vector3<float>(-3, 0.5, -0.5),
            Vector3<float>(1, 0, 0)
        )));
        EXPECT_TRUE(box.Intersect(Ray(
            Vector3<float>(1.5, 3, -0.5),
            Vector3<float>(0, -1, 0)
        )));
        EXPECT_TRUE(box.Intersect(Ray(
            Vector3<float>(1.5, -3, -0.5),
            Vector3<float>(0, 1, 0)
        )));
        EXPECT_FALSE(box.Intersect(Ray(
            Vector3<float>(1.5, 3, -0.5),
            Vector3<float>(0, 1, 0)
        )));
    }
}  // namespace rt
