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

#pragma once

#include "../Vector/Vector3.h"
#include "../Material/Material.h"

namespace rt {
    struct Ray {
        Ray(): Origin(), Direction() {};
        Ray(Vector3<float> const& origin, Vector3<float> const& dir): Origin(origin), Direction(dir) {};

        Vector3<float>  Origin;
        Vector3<float>  Direction;
    };

    struct Intersection {
        Intersection(): Intersect(false), Point(), Dist(-1), Normal() {};
        Intersection(bool intersect, Vector3<float> const& point, float const& dist, Vector3<float> const& normal, Material const& mat): Intersect(intersect), Point(point), Dist(dist), Normal(normal), Mat(mat) {};

        bool            Intersect;
        Vector3<float>  Point;
        float           Dist;
        Vector3<float>  Normal;
        Material        Mat;
    };
}  // namespace rt
