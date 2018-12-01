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

#include "gtest/gtest.h"
#include "Dispatcher.h"
#include "../Loader/OBJLoader.h"
#include "../Camera/Camera.h"
#include "../Vector/Vector2.h"

namespace rt {
    TEST(Dispatcher, start_and_stop) {
        objl::Loader loader;
        Engine engine = rt::Engine(loader, rt::Camera(rt::Vector3<float>(0, 0, -1),
                                                      rt::Vector2<int>(10, 10)));
        Dispatcher dispatcher(engine, Vector2<int>(10, 10));

        dispatcher.Start();
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Make sure the dispatcher had time to generate frames
        dispatcher.Stop();
        std::vector<rt::Color> const& image = dispatcher.Flush();
        bool empty = true;
        for (auto const& pixel : image) {
            if (pixel.GetColor().hexcode != 0x00000000) {
                empty = false;
            }
        }
        ASSERT_FALSE(empty);
    }
}  // namespace rt
