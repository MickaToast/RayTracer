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

#include "../Engine/Tools.h"
#include "Material.h"

namespace rt {
    Material::Material() {
        name = "";
        Ns = 96;
        Ka = Vector3<float>(0.75, 0.75, 0.75);
        Kd = Vector3<float>(0, 1, 0);
        Ks = Vector3<float>(0.5, 0.5, 0.5);
        Ke = Vector3<float>(0, 0, 0);
        Ni = 1.f;
        d = 1.f;
        illum = 0;
    }

    Material::~Material() {
    }

    Ray const Material::CreateNewRay(Intersection const& inter) {
        return Ray(inter.Point, inter.Normal);
    }
}  //namespace rt
