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

#include "SphereSky.h"

rt::SphereSky::SphereSky(const rt::Vector2<unsigned int> &size, const std::uint8_t *pixels) : _size(size), _pixels(pixels, pixels + (size.X * size.Y * 4)) {
}

rt::Color rt::SphereSky::GetPixel(const rt::Vector3<float> &direction) const {
    unsigned int u = (0.5f + (std::atan2(direction.Y, direction.X) / (2.f * static_cast<float>(M_PI)))) * (_size.X - 1);
    unsigned int v = (0.5f - std::asin(direction.Z) / static_cast<float>(M_PI)) * (_size.Y - 1);
    unsigned int index = (u * 4) + (v * 4 * _size.X);
    return Color(_pixels[index], _pixels[index + 1], _pixels[index + 2]);
}