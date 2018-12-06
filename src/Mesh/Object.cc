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

#include "Object.h"

namespace rt {
    Object::Object(std::vector<Triangle> const& triangles, Material const& mat) : _triangles(triangles), _KDTree(_triangles, _triangles.size()) {
        _material = mat;
    }

    Object::~Object() {

    }

    Intersection const Object::Intersect(Ray const& ray, Vector3<float> const& camPos) {
        return _KDTree.Intersect(ray, camPos);
    }

    Ray const Object::Refract(Ray const& ray) {
        (void)ray;
        return Ray(); //TODO
    }

    Ray const Object::Reflect(Ray const& ray) {
        (void)ray;
        return Ray(); //TODO
    }
}  // namespace rt