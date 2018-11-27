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

#pragma one

namespace rt {
class Vector2 {
 public:
    Vector2(void);
    Vector2(float X_, float Y);
    ~Vector2(void);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
    Vector2 operator+(const Vector2& right) const;
    Vector2 operator-(const Vector2& right) const;
    Vector2 operator*(const float& other) const;

    float const&    getX(void) const;
    void            SetX(const float& X);
    float const&    getY(void) const;
    void            SetY(const float& X);

 private:
    float   _X;
    float   _Y;
};
std::ostream& operator<<(std::ostream& os, const Vector2& v);
}  // namespace rt
