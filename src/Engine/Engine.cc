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

#include "Engine.h"
#include "Color.h"

namespace rt {
    Engine::Engine(objl::Loader const &loader, Camera const &camera) : _loader(loader), _camera(camera) {
    }

    Engine::~Engine() {
    }

    std::vector<Color> Engine::Generate(const Vector2 &from, const Vector2 &to) const {
        std::vector<Color> frame;
        Vector2 current(from);

        while (current != to) {
            frame.emplace_back(raytrace(current));
            current.SetX(current.GetX() + 1);
            if (current.GetX() > to.GetX()) {
                current.SetY(current.GetY() + 1);
                current.SetX(from.GetX());
            }
        }
        return frame;
    }

    Color Engine::raytrace(const rt::Vector2 &pixel) const {
        Color color(0x000000ff); // Black color
        //TODO: logic of raytracing a point will be here
        //TODO: _camera.generateRay(pixel);
        return color;
    }
}  // namespace rt
