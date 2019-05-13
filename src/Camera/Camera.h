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

#include <random>
#include <array>
#include "../Vector/Vector3.h"
#include "../Vector/Vector2.h"
#include "../Engine/Tools.h"

namespace rt {
    class Camera {
    public:
        Camera();
        virtual ~Camera();

        Ray const  GenerateRay(Vector2<unsigned int> const &pos);

        Vector3<float> const&                  GetPos() const;
        Vector2<unsigned int> const&           GetRes() const;
        void                                   SetMatrix(Vector3<float> const& pos, Vector3<float> const& c1, Vector3<float> const& c2, Vector3<float> const& c3);

    private:
        Vector3<float>                         _pos;
        Vector3<float>                         _c1;
        Vector3<float>                         _c2;
        Vector3<float>                         _c3;
        Vector2<unsigned int>                  _screenRes;
        Vector2<float>                         _screenSize;
        Vector3<float>                         _screenCorner;
        float                                  _screenDist;
        std::mt19937                           _gen;
        std::uniform_real_distribution<float>  _dis;


        void     generateScreen();
    };
}  // namespace rt
