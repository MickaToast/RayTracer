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

#include "../Engine/Constant.h"
#include "KDBox.h"

namespace rt {
    
    KDBox::KDBox(std::vector<Triangle> const& triangles) {
        this->setMinMax(triangles);
    }

    KDBox::~KDBox() {
    }

    bool KDBox::Intersect(Ray const& ray) {
        float tx1 = (_x.X - ray.Origin.X) / ray.Direction.X;
        float tx2 = (_x.Y - ray.Origin.X) / ray.Direction.X;
        float ty1 = (_y.X - ray.Origin.Y) / ray.Direction.Y;
        float ty2 = (_y.Y - ray.Origin.Y) / ray.Direction.Y;
        float tz1 = (_z.X - ray.Origin.Z) / ray.Direction.Z;
        float tz2 = (_z.Y - ray.Origin.Z) / ray.Direction.Z;
        float tMin = std::max(std::max(std::min(tx1, tx2), std::min(ty1, ty2)), std::min(tz1, tz2));
        float tMax = std::min(std::min(std::max(tx1, tx2), std::max(ty1, ty2)), std::max(tz1, tz2));
        if (tMin <= tMax) {
            if (tMin <= Constant::Epsilon && tMax <= Constant::Epsilon) return false;
            return true;
        }
        return false;
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
    
    std::size_t KDBox::GetLongestAxis() const {
        float xDiff = _x.Y - _x.X;
        float yDiff = _y.Y - _y.X;
        float zDiff = _z.Y - _z.X;
        float max = std::max(xDiff, std::max(yDiff, zDiff)); 
        return max == xDiff ? 0 : max == yDiff ? 1 : 2;
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
                if (x.X < _x.X) _x.X = x.X;
                if (x.Y > _x.Y) _x.Y = x.Y;
                if (y.X < _y.X) _y.X = y.X;
                if (y.Y > _y.Y) _y.Y = y.Y;
                if (z.X < _z.X) _z.X = z.X;
                if (z.Y > _z.Y) _z.Y = z.Y;
            }
        }
    }
}  // namespace rt
