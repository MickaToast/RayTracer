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

#include "Triangle.h"

namespace rt {
    Triangle::Triangle(Vector3<float> const& v1, Vector3<float> const& v2,
    Vector3<float> const& v3): _v1(v1), _v2(v2), _v3(v3) {
        _material.Ka = objl::Vector3(0, 1, 0);
        _material.Kd = objl::Vector3(0.75, 0.75, 0.75);
        _material.Ks = objl::Vector3(0.5, 0.5, 0.5);
        _material.illum = 0;
        _material.Ns = 96;
        this->generateCharacteristics();
    }

    Triangle::Triangle(Vector3<float> const& v1, Vector3<float> const& v2,
    Vector3<float> const& v3, objl::Material const& material): _v1(v1), _v2(v2), _v3(v3) {
        _material = material;
        this->generateCharacteristics();
    }

    Triangle::~Triangle() {
    }

    Intersection const Triangle::Intersect(Ray const& ray) {
        Intersection ret;
        Vector3<float> pvec = ray.Direction.Cross(_edge2);
        float det = _edge1.Dot(pvec);
        if (det < _epsilon) {
            ret.Intersect = false;
            return ret;
        }
        Vector3<float> tvec = ray.Origin - _v1;
        float u = tvec.Dot(pvec);
        if (u < 0.f || u > det) {
            ret.Intersect = false;
            return ret;
        }
        Vector3<float> qvec = tvec.Cross(_edge1);
        float v = ray.Direction.Dot(qvec);
        if (v < 0.0 || u + v > det) {
            ret.Intersect = false;
            return ret;
        }
        float t = _edge2.Dot(qvec) / det;
        ret.Intersect = true;
        ret.Point = ray.Origin + ray.Direction * t;
        return ret;
    }

    Ray const Triangle::Refract(Ray const& ray) {
        return Ray(); //TODO
    }

    Ray const Triangle::Reflect(Ray const& ray) {
        return Ray(); //TODO
    }

   Vector3<float> const& Triangle::GetEdge1() const {
       return _edge1;
   }

   Vector3<float> const& Triangle::GetEdge2() const {
       return _edge2;
   }

    void Triangle::generateCharacteristics() {
        _edge1 = _v2 - _v1;
        _edge2 = _v3 - _v1;
        _epsilon = 0.000001;
    }
} // namespace rt
