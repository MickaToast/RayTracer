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

#include <atomic>
#include <mutex>
#include <future>
#include "../Engine/Engine.h"
#include "../Vector/Vector2.h"

namespace rt {
    class Dispatcher {
    public:
        explicit                        Dispatcher(Engine const& engine, Vector2<int> const& res);
        virtual                         ~Dispatcher();

        void                            Start(void);
        void                            Stop(void);
        std::vector<Color> const&       Flush(void);

    private:
        void                            execute(void);

        bool                            _running;
        Engine                          _engine;
        Vector2<int>                    _res;
        std::vector<std::thread>        _threads;
        std::mutex                      _buffer_mutex;
        std::vector<std::vector<Color>> _buffer;
        std::vector<Color>              _image;
    };
}  // namespace rt
