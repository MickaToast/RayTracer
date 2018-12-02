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

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Loader/OBJLoader.h"
#include "Camera/Camera.h"
#include "Engine/Engine.h"
#include "Dispatcher/Dispatcher.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " scene.obj" << std::endl;
        return 1;
    }

    objl::Loader loader;

    std::cout << "Loading scene " << argv[1] << "..." << std::endl;
    if (!loader.LoadFile(argv[1])) {
        std::cerr << "Failed to load file. May have failed to "
                     "find it or it was not an .obj file." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(1600, 900), "RayTracer 2.0");
    window.setFramerateLimit(144);

    rt::Dispatcher dispatcher(rt::Engine(loader, rt::Camera(
            rt::Vector3<float>(0, 0, 5),
            rt::Vector3<float>(0, 0, -1),
            rt::Vector2<int>(window.getSize().x, window.getSize().y))),
            rt::Vector2<int>(window.getSize().x, window.getSize().y));

    dispatcher.Start(); //Start to dispatch

    sf::Uint8* frame = new sf::Uint8[window.getSize().x * window.getSize().y * 4];
    std::fill_n(frame, window.getSize().x * window.getSize().y * 4, 0xff); // Init with all component to 255
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        std::size_t i = 0;
        std::vector<rt::Color> pixels = dispatcher.Flush();

        for (auto const& pixel : pixels) {
            rt::Color_Component const& components = pixel.GetColor();
            frame[i] = components.rgba.r;
            frame[i + 1] = components.rgba.g;
            frame[i + 2] = components.rgba.b;
            i = i + 4;
        }
        texture.update(frame);

        window.clear();
        window.draw(sprite);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dispatcher.Stop();
                window.close();
            }
        }
    }

    return 0;
}
