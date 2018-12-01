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

#include <random>
#include <array>
#include "../Vector/Vector3.h"
#include "../Vector/Vector2.h"

namespace rt {
class Camera {
 public:
    Camera(Vector3<float> const& pos, Vector3<float> const& target, Vector2<int> const& res);
    explicit Camera(Vector3<float> const& target, Vector2<int> const& res);
    virtual ~Camera(void);

    Vector3<float>  GenerateRay(Vector2<int> const &pos);

    std::array<Vector3<float>, 3> const&  GetAxis(void) const;
    Vector2<int> const&                   GetRes(void) const;
    void                                  SetRes(const Vector2<int>& res);

 private:
    Vector3<float>                        _pos;
    std::array<Vector3<float>, 3>         _axis;
    float                                 _fov;
    Vector2<int>                          _screenRes;
    Vector2<float>                        _screenSize;
    Vector3<float>                        _screenCenter;
    Vector3<float>                        _screenCorner;
    float                                 _screenDist;
    std::mt19937                          _gen;
    std::uniform_real_distribution<float> _dis;


    void     generateAxis(Vector3<float> const& target);
    void     generateScreen();
};
}  // namespace rt
