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

#include <algorithm>
#include "Color.h"

rt::Color::Color() {
    _color.hexcode = 0x00000000;
}

rt::Color::Color(std::uint32_t hexcode) {
    _color.hexcode = hexcode;
}

rt::Color::Color(const rt::Color_Component &component) : _color(component) {
}

rt::Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    _color.rgba.r = red;
    _color.rgba.g = green;
    _color.rgba.b = blue;
}

rt::Color::Color(Vector3<float> const& vec) {
    _color.rgba.r = vec.X * 255;
    _color.rgba.g = vec.Y * 255;
    _color.rgba.b = vec.Z * 255;
}

rt::Color::~Color() {
}

rt::Color_Component rt::Color::GetColor() const {
    return _color;
}

void rt::Color::SetColor(const rt::Color_Component &component) {
    _color = component;
}

std::uint8_t const& rt::Color::GetRedComponent() const {
    return _color.rgba.r;
}

void rt::Color::SetRedComponent(std::uint8_t value) {
    _color.rgba.r = value;
}

std::uint8_t const& rt::Color::GetBlueComponent() const {
    return _color.rgba.b;
}

void rt::Color::SetBlueComponent(std::uint8_t value) {
    _color.rgba.b = value;
}

std::uint8_t const& rt::Color::GetGreenComponent() const {
    return _color.rgba.g;
}

void rt::Color::SetGreenComponent(std::uint8_t value) {
    _color.rgba.g = value;
}

rt::Color const& rt::Color::operator+=(rt::Color const& other) {
    _color.rgba.r = std::min(_color.rgba.r + other._color.rgba.r, 255);
    _color.rgba.g = std::min(_color.rgba.g + other._color.rgba.g, 255);
    _color.rgba.b = std::min(_color.rgba.b + other._color.rgba.b, 255);
    return *this;
}

rt::Color const rt::Color::operator*(float const& coef) {
    Color rtn;
    rtn._color.rgba.r = std::min(_color.rgba.r * coef, 255.f);
    rtn._color.rgba.g = std::min(_color.rgba.g * coef, 255.f);
    rtn._color.rgba.b = std::min(_color.rgba.b * coef, 255.f);
    return rtn;
}
