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

#include <cmath>
#include <iostream>
#include "Vector3.h"

namespace rt {
    Vector3::Vector3() {
        _X = 0.0f;
        _Y = 0.0f;
        _Z = 0.0f;
    }

    Vector3::Vector3(float X, float Y, float Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    Vector3::~Vector3(void) {
    }

    Vector3 Vector3::Cross(Vector3 const& other) const {
        return Vector3(_Y * other._Z - _Z * other._Y,
        _Z * other._X - _X * other._Z,
        _X * other._Y - _Y * other._X);
    }

    float Vector3::Dot(Vector3 const& other) const {
        return (_X * other._X) + (_Y * other._Y) + (_Z * other._Z);
    }

    float Vector3::Norm(void) const {
        return (std::sqrt(std::pow(_X, 2) + std::pow(_Y, 2) + std::pow(_Z, 2)));
    }

    void Vector3::Normalize(void) {
        float norm = this->Norm();
        _X = _X / norm;
        _Y = _Y / norm;
        _Z = _Z / norm;
    }

    bool Vector3::operator==(Vector3 const& other) const {
        return (_X == other._X && _Y == other._Y && _Z == other._Z);
    }

    bool Vector3::operator!=(Vector3 const& other) const {
        return !(_X == other._X && _Y == other._Y && _Z == other._Z);
    }

    Vector3 Vector3::operator+(Vector3 const& right) const {
        return Vector3(_X + right._X, _Y + right._Y, _Z + right._Z);
    }

    Vector3 Vector3::operator-(Vector3 const& right) const {
        return Vector3(_X - right._X, _Y - right._Y, _Z - right._Z);
    }

    Vector3 Vector3::operator*(float const& other) const {
        return Vector3(_X * other, _Y * other, _Z * other);
    }

    Vector3 Vector3::operator/(float const& other) const {
        return Vector3(_X / other, _Y / other, _Z / other);
    }

    std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
        return os;
    }

    float const& Vector3::getX(void) const {
        return _X;
    }

    void Vector3::SetX(float const& X) {
        _X = X;
    }

    float const& Vector3::getY(void) const {
        return _Y;
    }

    void Vector3::SetY(float const& Y) {
        _Y = Y;
    }

    float const& Vector3::getZ(void) const {
        return _Z;
    }

    void Vector3::SetZ(float const& Z) {
        _Z = Z;
    }
}  // namespace rt
