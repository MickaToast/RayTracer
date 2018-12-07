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
#include "Dispatcher.h"

namespace rt {
    Dispatcher::Dispatcher(const Engine &engine, Vector2<unsigned int> const& res) : _running(false), _engine(engine), _res(res), _image_index(0), _sample(0) {
        std::size_t size = _res.Y * _res.X;
        _image.reserve(size);
        _image.resize(size, Color(0x000000ff));
    }

    Dispatcher::~Dispatcher() {
    }

    void Dispatcher::Start() {
        _running = true;
        std::size_t cores = std::thread::hardware_concurrency();
        while (cores--) {
            _threads.emplace_back(std::thread(&Dispatcher::execute, this));
        }
        std::cout << "Dispatching over " << _threads.size() << " threads..." << std::endl;
    }

    void Dispatcher::Stop() {
        std::cout << "Shutting down threads..." << std::endl;
        _running = false;
        for (auto & thread : _threads) {
            thread.join();
        }
        _threads.clear();
    }

    std::vector<Color> Dispatcher::Flush() {
        return _image;
    }

    std::size_t Dispatcher::GetNumberOfProcessed() const {
        return _sample;
    }

    void Dispatcher::execute() {
        std::size_t size = _res.Y * _res.X;

        while (_running) {
            std::size_t current = _image_index++;
            if (current >= size) {
                _image_index = _image_index % size;
                current %= size;
                if (current == 0) {
                    _sample++;
                }
            }
            Color color = _engine.Raytrace(Vector2<unsigned int>(current % _res.X, current / _res.X));
            float coef1 = _sample / (_sample + 1.f);
            float coef2 = (_sample == 0 ? 1 : 1.f / (_sample + 1.f));
            _image_mutex.lock();
            _image[current].SetRedComponent(_image[current].GetRedComponent() * coef1 + color.GetRedComponent() * coef2);
            _image[current].SetGreenComponent(_image[current].GetGreenComponent() * coef1 + color.GetGreenComponent() * coef2);
            _image[current].SetBlueComponent(_image[current].GetBlueComponent() * coef1 + color.GetBlueComponent() * coef2);
            _image_mutex.unlock();
        }
    }
}  // namespace rt
