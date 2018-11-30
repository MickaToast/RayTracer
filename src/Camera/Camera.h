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

#include <array>
#include "../Vector/Vector3.h"
#include "../Vector/Vector2.h"

namespace rt {
class Camera {
 public:
    Camera(Vector3 const& pos, Vector3 const& target, Vector2 const& res);
    explicit Camera(Vector3 const& target, Vector2 const& res);
    virtual ~Camera(void);

    Vector3  GenerateRay(Vector2 const &pos) const;

    std::array<Vector3, 3> const& getAxis(void) const;
    Vector2 const&                getRes(void) const;
    void                          setRes(const Vector2& res);

 private:
    Vector3                 _pos = Vector3(0, 0, 0);
    std::array<Vector3, 3>  _axis;
    float                   _fov = 90.0;
    Vector2                 _screenRes;
    Vector2                 _screenSize;
    Vector3                 _screenCenter;
    Vector3                 _screenCorner;
    float                   _screenDist = 1;

    void     generateAxis(Vector3 const& target);
    void     generateScreen();
};
}  // namespace rt
