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
#include "Engine.h"
#include "Config.h"
#include "../Light/PointLight.h"

namespace rt {
    Engine::Engine(AssimpLoader const &loader) : _loader(loader), _camera(loader.GetCameraFromScene()) {
        _meshes = loader.GetMeshesFromScene();
        _lights = loader.GetLightsFromScene();
    }

    Engine::~Engine() {
    }

    Color Engine::Raytrace(const rt::Vector2<unsigned int> &pixel) {
        Color color = Color();
        Ray ray = _camera.GenerateRay(pixel);
        Intersection inter = _intersect(ray);
        if (inter.Intersect) {
            if (inter.Normal.Dot(ray.Direction) > 0) {
                inter.Normal = inter.Normal * -1;
            }
            for (size_t i = 0; i < _lights.size(); ++i) {
                Color lightColor;
                Vector3<float> lightDir = _lights[i]->GetPos() - inter.Point;
                lightDir.Normalize();
                Intersection interLight = _intersect(Ray(inter.Point, lightDir));
                if (!interLight.Intersect) {
                    float coef = lightDir.Dot(inter.Normal);
                    if (coef >= Config::Epsilon) {
                        coef *= 255;
                        lightColor.SetRedComponent(inter.Mat.Kd.X * coef);
                        lightColor.SetGreenComponent(inter.Mat.Kd.Y * coef);
                        lightColor.SetBlueComponent(inter.Mat.Kd.Z * coef);
                        color += lightColor;
                    }
                }
            }
        }
        return color;
    }

    /*void Engine::_pathtrace(Ray const& ray, unsigned int const& depth, Color & color) {

    }*/

    Intersection const Engine::_intersect(Ray const& ray) {
        Intersection rtn;
        float min = -1;

        for (size_t i = 0; i < _meshes.size(); ++i) {
            Intersection inter = _meshes[i]->Intersect(ray);
            if (inter.Intersect) {
                if (min == -1 || inter.Dist < min) {
                    min = inter.Dist;
                    rtn = inter;
                }
            }
        }
        return rtn;
    }

    Vector2<unsigned int> Engine::GetRes() const {
        return _camera.GetRes();
    }
}  // namespace rt
