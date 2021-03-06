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
#include "KDNode.h"

namespace rt {
    TEST(KDNode, raytrace) {
        std::vector<Triangle> triangles;        
        triangles.emplace_back(
            Vector3<float>(),
            Vector3<float>(1, 0, 0),
            Vector3<float>(0, 1, 0)
        );
        triangles.emplace_back(
            Vector3<float>(),
            Vector3<float>(0.5, 0, -3),
            Vector3<float>(1.5, 2, -0.5)
        );
        KDNode tree = KDNode(triangles, triangles.size());
        Intersection inter = tree.Intersect(Ray(
            Vector3<float>(0.01, 0, 1),
            Vector3<float>(0, .3, -1)
        ));
        EXPECT_TRUE(inter.Intersect);
    }
}  // namespace rt
