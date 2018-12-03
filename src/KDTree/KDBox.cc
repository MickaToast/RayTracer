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

#include "KDBox.h"

namespace rt {
    KDBox::KDBox(std::vector<Triangle> const& triangles) {
        this->setMinMax(triangles);
    }

    KDBox::~KDBox() {
    }

    Vector2<float> const& KDBox::GetX() const {
        return _x;
    }

    Vector2<float> const& KDBox::GetY() const {
        return _y;
    }

    Vector2<float> const& KDBox::GetZ() const {
        return _z;
    }

    void KDBox::setMinMax(std::vector<Triangle> const& triangles) {
        for (std::size_t i = 0; i < triangles.size(); ++i) {
            if (i == 0) {
                _x = triangles[i].GetMinMaxX();
                _y = triangles[i].GetMinMaxY();
                _z = triangles[i].GetMinMaxZ();
            } else {
                Vector2<float> x =  triangles[i].GetMinMaxX();
                Vector2<float> y =  triangles[i].GetMinMaxY();
                Vector2<float> z =  triangles[i].GetMinMaxZ();
                if (x.GetX() < _x.GetX()) _x.SetX(x.GetX());
                if (x.GetY() > _x.GetY()) _x.SetY(x.GetY());
                if (y.GetX() < _y.GetX()) _y.SetX(y.GetX());
                if (y.GetY() > _y.GetY()) _y.SetY(y.GetY());
                if (z.GetX() < _z.GetX()) _z.SetX(z.GetX());
                if (z.GetY() > _z.GetY()) _z.SetY(z.GetY());
            }
        }
    }
}  // namespace rt
