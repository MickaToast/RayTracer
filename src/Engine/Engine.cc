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
        std::vector<Triangle> triangles = loader.GetTrianglesFromScene();
        std::cout << "Creating KDTree for " << triangles.size() << " triangles." << std::endl;
        _KDTree = KDNode(triangles, triangles.size());
        std::cout << "KDTree created." << std::endl;
    }

    Engine::~Engine() {
    }

    Color Engine::raytrace(const rt::Vector2<unsigned int> &pixel) {
        return _KDTree.Raytrace(_camera.GenerateRay(pixel), _camera.GetPos()).color;
    }
}  // namespace rt
