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

#include <iostream>
#include <vector>
#include <thread>
#include "../Mesh/Triangle.h"
#include "Engine.h"
#include "Color.h"

namespace rt {
    Engine::Engine(AssimpLoader const &loader, Camera const &camera) : _loader(loader), _camera(camera) {
        _meshes = loader.GetMeshesFromScene();
        std::cout << "Meshes: " << _meshes.size() << std::endl;
    }

    Engine::~Engine() {
    }

    Color Engine::raytrace(const rt::Vector2<unsigned int> &pixel) {
        Color color = Color();
        Intersection inter;
        float min = -1;
        size_t idx = 0;
        Ray ray = _camera.GenerateRay(pixel);
        for (size_t i = 0; i < _meshes.size(); ++i) {
            inter = _meshes[i]->Intersect(ray, _camera.GetPos());
            if (inter.Intersect) {
                if (min == -1 || inter.Dist < min) {
                    min = inter.Dist;
                    idx = i;
                }
            }
        }
        if (min != -1) {
            Material mat = _meshes[idx]->GetMaterial();
            float angle = ray.Direction.Angle(inter.Normal);
            if (angle > 90.f) {
                angle = 180.f - angle;
            }
            float coef = ((-1.f / 90.f) * angle + 1.f) * 255.f;
            coef = 255;
            color.SetRedComponent(mat.Kd.X * coef);
            color.SetGreenComponent(mat.Kd.Y * coef);
            color.SetBlueComponent(mat.Kd.Z * coef);
        }
        return color;
    }
}  // namespace rt
