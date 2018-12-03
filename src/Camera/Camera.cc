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

namespace rt {
    Camera::Camera(Vector3<float> const& pos, Vector3<float> const& target,
    Vector2<unsigned int> const& res): _pos(pos), _fov(90.0f), _screenRes(res),
    _screenDist(1.f), _gen(std::random_device()()), _dis(0.f, 1.f) {
        _pos = pos;
        this->generateAxis(target);
        this->generateScreen();
    }

    Camera::Camera(Vector3<float> const& target, Vector2<unsigned int> const& res): _pos(Vector3<float>()),
     _fov(90.0f), _screenRes(res), _screenDist(1.f),
     _gen(std::random_device()()), _dis(0.f, 1.f) {
        this->generateAxis(target);
        this->generateScreen();
    }

    Camera::~Camera(void) {
    }

    Ray const Camera::GenerateRay(Vector2<unsigned int> const &pos) {
        #ifndef RT_TESTING_ENV
        float Rx = _dis(_gen);
        float Ry = _dis(_gen);
        #else
        float Rx = 0.0f;
        float Ry = 0.0f;
        #endif
        
        Vector3<float> pixel = (_screenCorner + (_axis[0] * _screenSize.GetX() * ((pos.GetX() + Rx) / _screenRes.GetX())))
        - (_axis[1] * _screenSize.GetY() * ((pos.GetY() + Ry) / _screenRes.GetY()));
        Vector3<float> dir = pixel - _pos;
        dir.Normalize();
        Ray ray(_pos, dir);
        return ray;
    }

    void Camera::generateAxis(Vector3<float> const& target) {
        _axis[2] = target - _pos;
        _axis[2].Normalize();
        _axis[0] = Vector3<float>(0, -1, 0).Cross(_axis[2]);
        _axis[0].Normalize();
        _axis[1] = _axis[0].Cross(_axis[2]);
        _axis[1].Normalize();
    }

    void Camera::generateScreen() {
      float screenWidth = 2.f * std::tan((_fov / 2.f) * static_cast<float>(M_PI) / 180.f)
        * _screenDist;
        _screenSize = Vector2<float>(screenWidth, screenWidth * _screenRes.GetY()
        / _screenRes.GetX());

        _screenCenter = _pos + _axis[2] * _screenDist;
        _screenCorner = (_screenCenter - _axis[0] * (_screenSize.GetX()
        / 2.f)) + _axis[1] * (_screenSize.GetY() / 2.f);
    }

    std::array<Vector3<float>, 3> const& Camera::GetAxis(void) const {
        return _axis;
    }

    Vector2<unsigned int> const& Camera::GetRes(void) const {
        return _screenRes;
    }

    Vector3<float> const& Camera::GetPos(void) const {
        return _pos;
    }

    void Camera::SetRes(const Vector2<unsigned int>& res) {
        _screenRes = res;
        this->generateScreen();
    }
}  // namespace rt
