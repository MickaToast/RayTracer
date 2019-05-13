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

#include <cstdlib>
#include <cmath>
#include "Camera.h"
#include "../Engine/Constant.h"

namespace rt {
    Camera::Camera() : _pos(Vector3<float>(0, 0, 0)), _c1(Vector3<float>(1, 0, 0)),
                       _c2(Vector3<float>(0, 1, 0)), _c3(Vector3<float>(0, 0, 1)),
                       _screenDist(1.f), _gen(std::random_device()()), _dis(0.f, 1.f) {
        generateScreen();
    }

    Camera::~Camera() {
    }

    Ray const Camera::GenerateRay(Vector2<unsigned int> const &pos) {
#ifndef RT_TESTING_ENV
        float Rx = _dis(_gen);
        float Ry = _dis(_gen);
#else
        float Rx = 0.0f;
        float Ry = 0.0f;
#endif
        Vector3<float> direction = (_screenCorner + _c1 * ((pos.X + Rx) / _screenRes.X) * _screenSize.X - _c2 * ((pos.Y + Ry) / _screenRes.Y) * _screenSize.Y - _pos) * _screenDist;
        direction.Normalize();
        Ray ray(_pos, direction);
        return ray;
    }

    Vector3<float> const& Camera::GetPos() const {
        return _pos;
    }

    Vector2<unsigned int> const& Camera::GetRes() const {
        return _screenRes;
    }

    void Camera::SetMatrix(Vector3<float> const& c1, Vector3<float> const& c2,
                           Vector3<float> const& c3, Vector3<float> const& pos) {
        _c1 = c1;
        _c2 = c2;
        _c3 = c3;
        _pos = pos;
        generateScreen();
    }

    void Camera::generateScreen() {
        _screenRes = Vector2<unsigned int>(Constant::DefaultScreenWidth, Constant::DefaultScreenHeight);
        float screenWidth = 2.f * std::tan((Constant::DefaultScreenFOV / 2.f) * static_cast<float>(M_PI) / 180.f) * _screenDist;
        _screenSize = Vector2<float>(screenWidth, screenWidth * _screenRes.Y / _screenRes.X);
        _screenCorner = _pos + _c3 * (-1.f) - _c1 * (_screenSize.X / 2.f) + _c2 * (_screenSize.Y / 2.f);
    }
}  // namespace rt
