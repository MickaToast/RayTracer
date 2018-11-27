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
#include <iostream>
#include "src/Camera/Camera.h"

namespace rt {
    Camera::Camera(Vector3 const& pos, Vector3 const& target) {
        _pos = pos;
        this->computeScreen(target);
    }

    Camera::Camera(Vector3 const& target) {
        this->computeScreen(target);
    }

    Camera::~Camera(void) {
    }

    Vector3 Camera::generateRay(Vector2 const &pos) const {
        float Rx = static_cast<double>(std::rand() / (RAND_MAX));
        float Ry = static_cast<double>(std::rand() / (RAND_MAX));
        Rx = 0;
        Ry = 0;
        Vector3 pixel = (_screenCorner + (_axis[0] * ((pos.getX() + Rx)
        / _screenRes.getX()))) + (_axis[1] * ((pos.getY() + Ry)
        / _screenRes.getY()));
        Vector3 ray = pixel - _pos;
        std::cout << "Pixel" << ray << std::endl;
//        ray.Normalize();
        return ray;
    }

    std::array<Vector3, 3> const& Camera::getAxis(void) const {
        return _axis;
    }

    void Camera::computeScreen(Vector3 const& target) {
        _axis[2] = target - _pos;
        _axis[2].Normalize();
        _axis[0] = Vector3(0, -1, 0).Cross(_axis[2]);
        _axis[0].Normalize();
        _axis[1] = _axis[0].Cross(_axis[2]);
        _axis[1].Normalize();

        float screenWidth = 2.f * std::tan((_fov / 2.f) * M_PI / 180.f)
        * _screenDist;
        std::cout << _screenRes.getY() / _screenRes.getX() << std::endl;
        std::cout << screenWidth << std::endl;
        std::cout << 1080.f / 1920.f << std::endl;
        _screenSize = Vector2(screenWidth, screenWidth * _screenRes.getY()
        / _screenRes.getX());

        _screenCenter = _pos + _axis[2] * _screenDist;
        _screenCorner = (_screenCenter - _axis[0] * (_screenSize.getX()
        / 2.f)) + _axis[1] * (_screenSize.getY() / 2.f);
    }
}  // namespace rt
