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
    KDBox::KDBox() {
    }

    KDBox::KDBox(std::vector<Triangle> const& triangles) {
        this->setMinMax(triangles);
        this->generateTriangles();
    }

    KDBox::~KDBox() {
    }

    bool KDBox::Intersect(Ray const& ray) {
        for (std::size_t i = 0; i < _triangles.size(); ++i) {
            if (_triangles[i].Intersect(ray).Intersect) {
                return true;
            }
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

    std::vector<Triangle> const& KDBox::GetTriangles() const{
        return _triangles;
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

    void KDBox::generateTriangles() {
        Vector3<float> A = Vector3<float>(_x.X, _y.X, _z.Y);
        Vector3<float> B = Vector3<float>(_x.X, _y.X, _z.X);
        Vector3<float> C = Vector3<float>(_x.Y, _y.X, _z.X);
        Vector3<float> D = Vector3<float>(_x.Y, _y.X, _z.Y);
        Vector3<float> E = Vector3<float>(_x.Y, _y.Y, _z.Y);
        Vector3<float> F = Vector3<float>(_x.X, _y.Y, _z.Y);
        Vector3<float> G = Vector3<float>(_x.X, _y.Y, _z.X);
        Vector3<float> H = Vector3<float>(_x.Y, _y.Y, _z.X);
        _triangles.push_back(Triangle(B, C, A));
        _triangles.push_back(Triangle(A, C, D));
        _triangles.push_back(Triangle(A, D, F));
        _triangles.push_back(Triangle(F, D, E));
        _triangles.push_back(Triangle(F, E, G));
        _triangles.push_back(Triangle(G, E, H));
        _triangles.push_back(Triangle(G, H, B));
        _triangles.push_back(Triangle(B, H, C));
        _triangles.push_back(Triangle(B, A, G));
        _triangles.push_back(Triangle(G, A, F));
        _triangles.push_back(Triangle(D, C, E));
        _triangles.push_back(Triangle(E, C, H));
    }
}  // namespace rt
