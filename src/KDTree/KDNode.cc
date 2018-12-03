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

#include "KDNode.h"

namespace rt {
    KDNode::KDNode() : _box() {
    }

    KDNode::KDNode(std::vector<Triangle> const& triangles, std::size_t const& totalSize): _box(triangles) {
        _left = nullptr;
        _right = nullptr;
        std::size_t size = triangles.size();
        if (size > std::max(24.f, totalSize / 2000.f)) {
            std::vector<Triangle> tleft;
            std::vector<Triangle> tright;
            Vector3<float> midpoint;
            for (std::size_t i = 0; i < size; ++i) {
                midpoint = midpoint + triangles[i].GetMidPoint() / static_cast<float>(size);
            }
            std::size_t axis = _box.GetLongestAxis();
            for (std::size_t i = 0; i < size; ++i) {
                switch (axis) {
                    case 0:
                        triangles[i].GetMidPoint().X > midpoint.X ? tright.push_back(triangles[i]) : tleft.push_back(triangles[i]);
                        break;
                    case 1:
                        triangles[i].GetMidPoint().Y > midpoint.Y ? tright.push_back(triangles[i]) : tleft.push_back(triangles[i]);
                        break;
                    case 2:
                        triangles[i].GetMidPoint().Z > midpoint.Z ? tright.push_back(triangles[i]) : tleft.push_back(triangles[i]);
                        break;
                }
            }
            _left = new KDNode(tleft, totalSize);
            _right = new KDNode(tright, totalSize);
        } else {
            _triangles = triangles;
        }
    }

    KDNode::~KDNode() {
    }

    KDTreeIntersection KDNode::Raytrace(Ray const& ray, Vector3<float> const& camPos) {
        KDTreeIntersection intersection = KDTreeIntersection();
        if (!(_box.Intersect(ray))) {
            return intersection;
        } else if (!_left) {
            Intersection inter;
            float min = -1;
            for (std::size_t i = 0; i < _triangles.size(); ++i) {
                inter = _triangles[i].Intersect(ray);
                if (inter.Intersect) {
                    intersection.Intersect = true;
                    Vector3<float> dist = inter.Point - camPos;
                    if (min == -1 || dist.Norm() < min) {
                        min = dist.Norm();
                        float angle = ray.Direction.Angle(_triangles[i].GetNormal());
                        if (angle > 90.f) {
                            angle = 180.f - angle;
                        }
                        float coef = ((-1.f / 90.f) * angle + 1.f) * 255.f;
                        intersection.color.SetRedComponent(_triangles[i].GetMaterial().Ka.X * coef);
                        intersection.color.SetGreenComponent(_triangles[i].GetMaterial().Ka.Y * coef);
                        intersection.color.SetBlueComponent(_triangles[i].GetMaterial().Ka.Z * coef);
                    }
                }
            }
            return intersection;
        } else {
            KDTreeIntersection left = _left->Raytrace(ray, camPos);
            KDTreeIntersection right = _right->Raytrace(ray, camPos);
            return left.Intersect ? left : right;
        }
    }
}  //namespace rt
