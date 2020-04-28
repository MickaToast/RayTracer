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

#include <cstdint>
#include "../Vector/Vector3.h"

namespace rt {
    union Color_Component {
        std::uint32_t   hexcode;
        struct rgbaTag {
            std::uint8_t    a;
            std::uint8_t    b;
            std::uint8_t    g;
            std::uint8_t    r;
        } rgba;
    };

    class Color {
    public:
        explicit    Color();
        explicit    Color(std::uint32_t hexcode);
        explicit    Color(Color_Component const& component);
        explicit    Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue);
        explicit    Color(Vector3<float> const& vec);
        virtual     ~Color();

        Color_Component     GetColor() const;
        void                SetColor(Color_Component const& component);
        std::uint8_t const& GetRedComponent() const;
        void                SetRedComponent(std::uint8_t value);
        std::uint8_t const& GetBlueComponent() const;
        void                SetBlueComponent(std::uint8_t value);
        std::uint8_t const& GetGreenComponent() const;
        void                SetGreenComponent(std::uint8_t value);

        Color const& operator+=(Color const& other);
        Color const operator*(float const& coef);

    private:
        Color_Component _color;
    };
}