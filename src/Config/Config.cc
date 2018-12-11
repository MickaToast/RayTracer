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

#include "Config.h"
#include <iostream>

rt::Config::Config() : _outputImageFrames(0) {
}

void rt::Config::LoadFromArguments(int argc, char **argv) {
    int i = 2;

    while (i < argc) {
        std::string current(argv[i]);
        if (current.find('=') != std::string::npos) {
            std::string left(current.substr(0, current.find('=')));
            std::string right(current.substr(current.find('=') + 1));

            if (left == "--background-image") {
                _backgroundPath = right;
            } else if (left == "--output-image") {
                _outputImageFrames = std::stoul(right);
            } else {
                std::cerr << "Warning: " << left << " is not a recognized option" << std::endl;
            }
        }
        i++;
    }
}

bool rt::Config::RequestImageOutput() const {
    return _outputImageFrames != 0;
}

std::size_t rt::Config::GetImageOutputFrames() const {
    return _outputImageFrames;
}

bool rt::Config::RequestBackground() const {
    return !_backgroundPath.empty();
}

std::string rt::Config::GetBackgroundPath() const {
    return _backgroundPath;
}