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
#include "../Engine/Config.h"

namespace rt {
    Triangle::Triangle(Vertex const& v1, Vertex const& v2,
    Vertex const& v3): _v1(v1), _v2(v2), _v3(v3) {
        this->generateCharacteristics();
    }

    Triangle::Triangle(Vertex const& v1, Vertex const& v2,
    Vertex const& v3, Material const& material): _v1(v1), _v2(v2), _v3(v3) {
        _material = material;
        this->generateCharacteristics();
    }

    Triangle::~Triangle() {
    }

    Intersection const Triangle::Intersect(Ray const& ray) {
        Intersection ret;
        Vector3<float> pvec = ray.Direction.Cross(_edge2);
        float det = _edge1.Dot(pvec);
        if (det > -Config::Epsilon && det < Config::Epsilon) {
            return ret;
        }
        Vector3<float> tvec = ray.Origin - _v1.GetPos();
        float u = tvec.Dot(pvec) / det;
        if (u < 0.f || u > 1.f) {
            return ret;
        }
        Vector3<float> qvec = tvec.Cross(_edge1);
        float v = ray.Direction.Dot(qvec) / det;
        if (v < 0.f || u + v > 1.f) {
            return ret;
        }
        float t = _edge2.Dot(qvec) / det;
        if (t < Config::MinDist) {
            return ret;
        }
        ret.Intersect = true;
        ret.Point = ray.Origin + ray.Direction * t;
        ret.Dist = t;
        if (_v1.GetNormal() != Vector3<float>()) {
            ret.Normal = _v1.GetNormal() * (1 - u - v) + _v2.GetNormal() * u + _v3.GetNormal() * v;
        } else {
            ret.Normal = _normal;
        }
        ret.Mat = _material;
        return ret;
    }

   Vector2<float> const Triangle::GetMinMaxX() const {
       return Vector2<float>(
           std::min(_v1.GetPos().X, std::min(_v2.GetPos().X, _v3.GetPos().X)),
           std::max(_v1.GetPos().X, std::max(_v2.GetPos().X, _v3.GetPos().X))
       );
   }

   Vector2<float> const Triangle::GetMinMaxY() const {
       return Vector2<float>(
           std::min(_v1.GetPos().Y, std::min(_v2.GetPos().Y, _v3.GetPos().Y)),
           std::max(_v1.GetPos().Y, std::max(_v2.GetPos().Y, _v3.GetPos().Y))
       );
   }

   Vector2<float> const Triangle::GetMinMaxZ() const {
       return Vector2<float>(
           std::min(_v1.GetPos().Z, std::min(_v2.GetPos().Z, _v3.GetPos().Z)),
           std::max(_v1.GetPos().Z, std::max(_v2.GetPos().Z, _v3.GetPos().Z))
       );
   }

   Vector3<float> const Triangle::GetMidPoint() const {
       return Vector3<float>(
            (this->GetMinMaxX().X + this->GetMinMaxX().Y) / 2.f,
            (this->GetMinMaxY().X + this->GetMinMaxY().Y) / 2.f,
            (this->GetMinMaxZ().X + this->GetMinMaxZ().Y) / 2.f
        );
   }

   Vertex const& Triangle::GetV1() const {
       return _v1;
   }

   Vertex const& Triangle::GetV2() const {
       return _v2;
   }

   Vertex const& Triangle::GetV3() const {
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
        _edge1 = _v2.GetPos() - _v1.GetPos();
        _edge2 = _v3.GetPos() - _v1.GetPos();
        _normal = _edge1.Cross(_edge2);
        _normal.Normalize();
    }
} // namespace rt
