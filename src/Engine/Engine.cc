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

#include <thread>
#include "Engine.h"
#include "Color.h"

namespace rt {
    Engine::Engine(objl::Loader const &loader, Camera const &camera) : _loader(loader), _camera(camera) {
        for (std::size_t i = 0; i < _loader.LoadedVertices.size(); i += 3) {
            _triangles.push_back(Triangle(
                Vector3<float>(
                    _loader.LoadedVertices[i].Position.X,
                    _loader.LoadedVertices[i].Position.Y,
                    _loader.LoadedVertices[i].Position.Z
                ),
                Vector3<float>(
                    _loader.LoadedVertices[i + 1].Position.X,
                    _loader.LoadedVertices[i + 1].Position.Y,
                    _loader.LoadedVertices[i + 1].Position.Z
                ),
                Vector3<float>(
                    _loader.LoadedVertices[i + 2].Position.X,
                    _loader.LoadedVertices[i + 2].Position.Y,
                    _loader.LoadedVertices[i + 2].Position.Z
                )
            ));
        }
    }

    Engine::~Engine() {
    }

    Color Engine::raytrace(const rt::Vector2<unsigned int> &pixel) {
        Color color = Color();
        float min = -1;
        Intersection inter;
        Ray ray = _camera.GenerateRay(pixel);
        for (std::size_t i = 0; i < _triangles.size(); ++i) { //TODO: KDTree
            inter = _triangles[i].Intersect(ray);
            if (inter.Intersect) {
                Vector3<float> dist = inter.Point - _camera.GetPos();
                if (min == -1 || dist.Norm() < min) {
                    min = dist.Norm();
                    float angle = ray.Direction.Angle(_triangles[i].GetNormal());
                    if (angle > 90.f) {
                        angle = 180.f - angle;
                    }
                    float coef = ((-1.f / 90.f) * angle + 1.f) * 255.f;
                    color.SetRedComponent(_triangles[i].GetMaterial().Ka.X * coef);
                    color.SetGreenComponent(_triangles[i].GetMaterial().Ka.Y * coef);
                    color.SetBlueComponent(_triangles[i].GetMaterial().Ka.Z * coef);
                }
            }
        }
        return color;
    }
}  // namespace rt
