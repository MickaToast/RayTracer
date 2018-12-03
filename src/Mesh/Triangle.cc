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
#include "Triangle.h"
#include "../Vector/Vector2.h"

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
        if (std::abs(det) < _epsilon) {
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
        if (v < 0.f || u + v > det) {
            ret.Intersect = false;
            return ret;
        }
        float t = _edge2.Dot(qvec) / det;
        if (t < 0.f) {
            ret.Intersect = false;
            return ret;
        }
        ret.Intersect = true;
        ret.Point = ray.Origin + ray.Direction * t;
        return ret;
    }

    Ray const Triangle::Refract(Ray const& ray) {
        (void)ray;
        return Ray(); //TODO
    }

    Ray const Triangle::Reflect(Ray const& ray) {
        (void)ray;
        return Ray(); //TODO
    }

   Vector2<float> const Triangle::GetMinMaxX() const {
       return Vector2<float>(
           std::min(_v1.GetX(), std::min(_v2.GetX(), _v3.GetX())),
           std::max(_v1.GetX(), std::max(_v2.GetX(), _v3.GetX()))
       );
   }

   Vector2<float> const Triangle::GetMinMaxY() const {
       return Vector2<float>(
           std::min(_v1.GetY(), std::min(_v2.GetY(), _v3.GetY())),
           std::max(_v1.GetY(), std::max(_v2.GetY(), _v3.GetY()))
       );
   }

   Vector2<float> const Triangle::GetMinMaxZ() const {
       return Vector2<float>(
           std::min(_v1.GetZ(), std::min(_v2.GetZ(), _v3.GetZ())),
           std::max(_v1.GetZ(), std::max(_v2.GetZ(), _v3.GetZ()))
       );
   }

   Vector3<float> const Triangle::GetMidPoint() const {
       return Vector3<float>(
            (this->GetMinMaxX().GetX() + this->GetMinMaxX().GetY()) / 2.f,
            (this->GetMinMaxY().GetX() + this->GetMinMaxY().GetY()) / 2.f,
            (this->GetMinMaxZ().GetX() + this->GetMinMaxZ().GetY()) / 2.f
        );
   }

   Vector3<float> const& Triangle::GetV1() const {
       return _v1;
   }

   Vector3<float> const& Triangle::GetV2() const {
       return _v2;
   }

   Vector3<float> const& Triangle::GetV3() const {
       return _v3;
   }

   Vector3<float> const& Triangle::GetEdge1() const {
       return _edge1;
   }

   Vector3<float> const& Triangle::GetEdge2() const {
       return _edge2;
   }

   Vector3<float> const& Triangle::GetNormal() const {
       return _normal;
   }
   
   bool  Triangle::operator==(Triangle const& other) const {
       return (_v1 == other.GetV1() && _v2 == other.GetV2() && _v3 == other.GetV3());
   }

    void Triangle::generateCharacteristics() {
        _edge1 = _v2 - _v1;
        _edge2 = _v3 - _v1;
        _epsilon = 0.000001;
        _normal = _edge1.Cross(_edge2);
        _normal.Normalize();
    }
} // namespace rt
