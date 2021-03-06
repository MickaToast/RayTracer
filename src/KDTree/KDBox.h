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

#include <vector>
#include "../Mesh/Triangle.h"
#include "../Engine/Tools.h"
#include "../Engine/Color.h"

namespace rt {
class KDBox {
 public:
    KDBox(std::vector<Triangle> const& triangles);
    ~KDBox();

    bool    Intersect(Ray const& ray);

    Vector2<float> const&           GetX() const;
    Vector2<float> const&           GetY() const;
    Vector2<float> const&           GetZ() const;
    std::size_t                     GetLongestAxis() const;

 private:
    Vector2<float>          _x;  // Containing Xmin and Xmax
    Vector2<float>          _y;  // Containing Ymin and Ymax
    Vector2<float>          _z;  // Containing Zmin and Zmax

    void    setMinMax(std::vector<Triangle> const& triangles);
};
}  // namespace rt
