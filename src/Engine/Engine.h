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

#include <memory>
#include "../Camera/Camera.h"
#include "../Loader/AssimpLoader.h"
#include "../KDTree/KDNode.h"
#include "../Vector/Vector2.h"
#include "../Vector/Vector3.h"
#include "Color.h"

namespace rt {
    class Engine {
    public:
        explicit    Engine(AssimpLoader const& loader);
        virtual     ~Engine();

        Color                   Raytrace(Vector2<unsigned int> const& pixel);
        Vector2<unsigned int>   GetRes() const;

    private:
        AssimpLoader                        _loader;
        Camera                              _camera;
        std::vector<std::shared_ptr<Mesh>>  _meshes;
    };
}  // namespace rt
