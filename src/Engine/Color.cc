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

#include "Color.h"

rt::Color::Color() {
    _color.hexcode = 0x00000000;
}

rt::Color::Color(std::uint32_t hexcode) {
    _color.hexcode = hexcode;
}

rt::Color::Color(const rt::Color_Component &component) : _color(component) {
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

std::uint8_t const& rt::Color::GetAlphaComponent() const {
    return _color.rgba.a;
}

void rt::Color::SetAlphaComponent(std::uint8_t value) {
    _color.rgba.a = value;
}