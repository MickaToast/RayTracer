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

#include <cmath>
#include <iostream>
#include "Vector2.h"

namespace rt {
    template <class T>
    class Vector3 : public Vector2<T> {
    public:
        Vector3(void) : _Z(0) {
            this->_X = 0;
            this->_Y = 0;
        };
        Vector3(T X, T Y, T Z) : _Z(Z) {
            this->_X = X;
            this->_Y = Y;
        };
        virtual ~Vector3(void) {};

        Vector3<T> Cross(Vector3<T> const& other) const {
            return Vector3<T>(this->_Y * other._Z - _Z * other._Y,
                           _Z * other._X - this->_X * other._Z,
                           this->_X * other._Y - this->_Y * other._X);
        }

        T   Dot(Vector3<T> const& other) const {
            return (this->_X * other._X) + (this->_Y * other._Y) + (_Z * other._Z);
        }

        T   Norm(void) const {
            return (std::sqrt(std::pow(this->_X, 2) + std::pow(this->_Y, 2) + std::pow(_Z, 2)));
        }

        void    Normalize(void) {
            float norm = this->Norm();
            this->_X = this->_X / norm;
            this->_Y = this->_Y / norm;
            _Z = _Z / norm;
        }

        bool    operator==(Vector3 const& other) const {
            return (this->_X == other._X && this->_Y == other._Y && _Z == other._Z);
        }

        bool    operator!=(Vector3 const& other) const {
            return (this->_X != other._X || this->_Y != other._Y || _Z != other._Z);
        }

        Vector3 operator+(Vector3 const& right) const {
            return Vector3(this->_X + right._X, this->_Y + right._Y, _Z + right._Z);
        }

        Vector3 operator-(Vector3 const& right) const {
            return Vector3(this->_X - right._X, this->_Y - right._Y, _Z - right._Z);
        }

        Vector3 operator*(T const& other) const {
            return Vector3(this->_X * other, this->_Y * other, _Z * other);
        }

        Vector3 operator/(T const& other) const {
            return Vector3(this->_X / other, this->_Y / other, _Z / other);
        }
        
        T const&    GetZ(void) const {
            return _Z;
        }

        void        SetZ(T const& Z) {
            _Z = Z;
        }

    private:
        T   _Z;
    };

    template <class T>
    std::ostream& operator<<(std::ostream& out, const Vector3<T>& v) {
        std::cout << "(" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")";
        return out;
    }
}  // namespace rt
