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

namespace rt {
class Vector2 {
 public:
    Vector2(void);
    Vector2(float X_, float Y);
    ~Vector2(void);

    bool    operator==(Vector2 const& other) const;
    bool    operator!=(Vector2 const& other) const;
    Vector2 operator+(Vector2 const& right) const;
    Vector2 operator-(Vector2 const& right) const;
    Vector2 operator*(float const& other) const;
    Vector2 operator/(float const& other) const;

    float const&    GetX(void) const;
    void            SetX(float const& X);
    float const&    GetY(void) const;
    void            SetY(float const& X);

 private:
    float   _X;
    float   _Y;
};
std::ostream& operator<<(std::ostream& os, Vector2 const& v);
}  // namespace rt
