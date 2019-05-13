#include <memory>

#include <memory>

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

#include "../Engine/Constant.h"
#include "KDNode.h"

namespace rt {
    KDNode::KDNode(std::vector<Triangle> const& triangles, std::size_t depth): _box(triangles), _left(nullptr), _right(nullptr) {
        std::size_t size = triangles.size();
        if (triangles.size() > Constant::KDTreeMin && depth) {
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
            _left = std::make_shared<KDNode>(tleft, depth - 1);
            _right = std::make_shared<KDNode>(tright, depth - 1);
        } else {
            _triangles = triangles;
        }
    }

    Intersection KDNode::Intersect(Ray const& ray) {
        Intersection intersection = Intersection();
        if (!(_box.Intersect(ray))) {
            return intersection;
        } else if (!_left && !_right) {
            Intersection inter;
            float min = -1;
            for (auto & _triangle : _triangles) {
                inter = _triangle.Intersect(ray);
                if (inter.Intersect) {
                    if (min == -1 || inter.Dist < min) {
                        min = inter.Dist;
                        intersection = inter;
                    }
                }
            }
            return intersection;
        } else {
            Intersection left = _left->Intersect(ray);
            Intersection right = _right->Intersect(ray);

            if (left.Intersect && right.Intersect) {
                return left.Dist < right.Dist ? left : right;
            }
            return left.Intersect ? left : right.Intersect ? right : intersection;
        }
    }
}  //namespace rt
