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
    struct Vector3 : public Vector2<T> {
    public:
        Vector3(void) : Z(0) {
            this->X = 0;
            this->Y = 0;
        };
        Vector3(T _X, T _Y, T _Z) : Z(_Z) {
            this->X = _X;
            this->Y = _Y;
        };
        virtual ~Vector3(void) {};

        Vector3<T> Cross(Vector3<T> const& other) const {
            return Vector3<T>(this->Y * other.Z - Z * other.Y,
                           Z * other.X - this->X * other.Z,
                           this->X * other.Y - this->Y * other.X);
        }

        T   Dot(Vector3<T> const& other) const {
            return (this->X * other.X) + (this->Y * other.Y) + (Z * other.Z);
        }

        T   Norm(void) const {
            return (std::sqrt(std::pow(this->X, 2) + std::pow(this->Y, 2) + std::pow(Z, 2)));
        }

        T   Angle(Vector3<T> const & other) const {
            return std::acos(this->Dot(other) / (this->Norm() * other.Norm())) * 180.f / static_cast<float>(M_PI);
        }

        void    Normalize(void) {
            float norm = this->Norm();
            this->X = this->X / norm;
            this->Y = this->Y / norm;
            Z = Z / norm;
        }

        bool    operator==(Vector3 const& other) const {
            return (this->X == other.X && this->Y == other.Y && Z == other.Z);
        }

        bool    operator!=(Vector3 const& other) const {
            return (this->X != other.X || this->Y != other.Y || Z != other.Z);
        }

        Vector3 operator+(Vector3 const& right) const {
            return Vector3(this->X + right.X, this->Y + right.Y, Z + right.Z);
        }

        Vector3 operator-(Vector3 const& right) const {
            return Vector3(this->X - right.X, this->Y - right.Y, Z - right.Z);
        }

        Vector3 operator*(T const& other) const {
            return Vector3(this->X * other, this->Y * other, Z * other);
        }

        Vector3 operator/(T const& other) const {
            return Vector3(this->X / other, this->Y / other, Z / other);
        }

        T   Z;
    };

    template <class T>
    std::ostream& operator<<(std::ostream& out, const Vector3<T>& v) {
        out << "(" << v.X << ", " << v.Y << ", " << v.Z << ")";
        return out;
    }
}  // namespace rt
