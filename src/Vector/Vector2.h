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

#include <iostream>

namespace rt {
    template <class T>
    struct Vector2 {
    public:
        Vector2(void) : X(0), Y(0) {};
        Vector2(T _X, T _Y) : X(_X), Y(_Y) {};
        virtual ~Vector2(void) {};

        bool    operator==(Vector2<T> const& other) const {
            return (X == other.X && Y == other.Y);
        }

        bool    operator!=(Vector2<T> const& other) const {
            return (X != other.X || Y != other.Y);
        }

        Vector2<T> operator+(Vector2<T> const& right) const {
            return Vector2<T>(X + right.X, Y + right.Y);
        }

        Vector2<T> operator-(Vector2<T> const& right) const {
            return Vector2<T>(X - right.X, Y - right.Y);
        }

        Vector2<T> operator*(T const& other) const {
            return Vector2<T>(X * other, Y * other);
        }

        Vector2<T> operator/(T const& other) const {
            return Vector2<T>(X / other, Y / other);
        }

        T   X;
        T   Y;
    };

    template <class T>
    std::ostream& operator<<(std::ostream& out, const Vector2<T>& v) {
        out << "(" << v.X << ", " << v.Y << ")";
        return out;
    }
}  // namespace rt
