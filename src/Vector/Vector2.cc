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

#include <iostream>
#include "Vector2.h"

namespace rt {
    Vector2::Vector2() {
        _X = 0.0f;
        _Y = 0.0f;
    }

    Vector2::Vector2(float X, float Y) {
        _X = X;
        _Y = Y;
    }

    Vector2::~Vector2(void) {
    }

    bool Vector2::operator==(Vector2 const& other) const {
        return (_X == other._X && _Y == other._Y);
    }

    bool Vector2::operator!=(Vector2 const& other) const {
        return !(_X == other._X && _Y == other._Y);
    }

    Vector2 Vector2::operator+(Vector2 const& right) const {
        return Vector2(_X + right._X, _Y + right._Y);
    }

    Vector2 Vector2::operator-(Vector2 const& right) const {
        return Vector2(_X - right._X, _Y - right._Y);
    }

    Vector2 Vector2::operator*(float const& other) const {
        return Vector2(_X * other, _Y * other);
    }

    Vector2 Vector2::operator/(float const& other) const {
        return Vector2(_X / other, _Y / other);
    }

    std::ostream& operator<<(std::ostream& os, Vector2 const& v) {
        os << "(" << v.GetX() << "," << v.GetY() << ")";
        return os;
    }

    float const& Vector2::GetX(void) const {
        return _X;
    }

    void Vector2::SetX(float const& X) {
        _X = X;
    }

    float const& Vector2::GetY(void) const {
        return _Y;
    }

    void Vector2::SetY(float const& Y) {
        _Y = Y;
    }
}  // namespace rt
