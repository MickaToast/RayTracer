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

#include "Mesh.h"
#include "../Material/Material.h"
#include "../Vector/Vector3.h"

namespace rt {
class Triangle : public Mesh {
 public:
    Triangle(Vector3<float> const& v1, Vector3<float> const& v2, Vector3<float> const& v3);
    Triangle(Vector3<float> const& v1, Vector3<float> const& v2, Vector3<float> const& v3, Material const& material);
    ~Triangle();

    virtual Intersection const  Intersect(Ray const& ray);
    virtual Ray const           Refract(Ray const& ray);
    virtual Ray const           Reflect(Ray const& ray);

   Vector2<float> const    GetMinMaxX() const;
   Vector2<float> const    GetMinMaxY() const;
   Vector2<float> const    GetMinMaxZ() const;
   Vector3<float> const    GetMidPoint() const;
   Vector3<float> const&   GetV1() const;
   Vector3<float> const&   GetV2() const;
   Vector3<float> const&   GetV3() const;
   Vector3<float> const&   GetEdge1() const;
   Vector3<float> const&   GetEdge2() const;
   Vector3<float> const&   GetNormal() const;

   bool  operator==(Triangle const& other) const;

 private:
    Vector3<float>  _v1;
    Vector3<float>  _v2;
    Vector3<float>  _v3;
    Vector3<float>  _normal;
    Vector3<float>  _edge1;
    Vector3<float>  _edge2;

    void    generateCharacteristics();
};
}  // namespace rt
