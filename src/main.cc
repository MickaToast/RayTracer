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

    sf::RenderWindow window(sf::VideoMode(1280, 720), "RayTracer 2.0");
    window.setFramerateLimit(10);
    std::srand(std::time(0));
    rt::Engine engine(loader, rt::Camera(rt::Vector3(0, 0, -1)));
    sf::Uint8* pixels = new sf::Uint8[window.getSize().x * window.getSize().y * 4];
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        std::vector<rt::Color> frame = engine.Generate(rt::Vector2(0, 0), rt::Vector2(window.getSize().x - 1, window.getSize().y - 1));

        int i = 0;
        for (rt::Color const& pixel : frame) {
            pixels[i] = pixel.GetColor().rgba.r;
            pixels[i + 1] = pixel.GetColor().rgba.g;
            pixels[i + 2] = pixel.GetColor().rgba.b;
            pixels[i + 3] = pixel.GetColor().rgba.a;
            i += 4;
        }
        texture.update(pixels);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
