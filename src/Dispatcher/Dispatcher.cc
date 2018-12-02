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
    Dispatcher::Dispatcher(const Engine &engine, Vector2<int> const& res) : _running(false), _engine(engine), _res(res), _sample(0) {
        std::size_t size = _res.GetY() * _res.GetX();
        _image.reserve(size);
        _image.resize(size);
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

    std::vector<Color> const& Dispatcher::Flush() {
        std::size_t size = _res.GetY() * _res.GetX();

        _buffer_mutex.lock();
        for (auto const& frame : _buffer) {
            std::size_t i = 0;
            float coef1 = _sample / (_sample + 1.f);
            float coef2 = (_sample == 0 ? 1 : 1.f / (_sample + 1));
            while (i < size) {
                _image[i].SetRedComponent(_image[i].GetRedComponent() * coef1 + frame[i].GetRedComponent() * coef2);
                _image[i].SetGreenComponent(_image[i].GetGreenComponent() * coef1 + frame[i].GetGreenComponent() * coef2);
                _image[i].SetBlueComponent(_image[i].GetBlueComponent() * coef1 + frame[i].GetBlueComponent() * coef2);
                i++;
            }
            _sample++;
        }
        _buffer.clear();
        _buffer_mutex.unlock();
        return _image;
    }

    void Dispatcher::execute() {
        std::vector<Color> frame;
        Vector2<int> current(0, 0);
        std::size_t i;
        std::size_t size = _res.GetY() * _res.GetX();

        frame.reserve(size);
        frame.resize(size);
        while (_running) {
            current.SetX(0);
            current.SetY(0);
            i = 0;
            while (current.GetY() < _res.GetY() - 1 || current.GetX() < _res.GetX() - 1) {
                frame[i] = this->_engine.raytrace(current);
                current.SetX(current.GetX() + 1);
                if (current.GetX() > _res.GetX() - 1) {
                    current.SetX(0);
                    current.SetY(current.GetY() + 1);
                }
                i++;
            }
            _buffer_mutex.lock();
            _buffer.push_back(frame);
            _buffer_mutex.unlock();
        }
    }
}  // namespace rt
