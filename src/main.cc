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
#include <cstring>
#include <regex>
#include "Loader/Bitmap.h"
#include "Loader/AssimpLoader.h"
#include "Camera/Camera.h"
#include "Engine/Engine.h"
#include "Dispatcher/Dispatcher.h"
#include "Vector/Vector2.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage 1: " << argv[0] << " scene.dae" << std::endl;
        std::cerr << "Usage 3: " << argv[0] << " scene.obj --output-image 5" << std::endl;
        return 1;
    }

    rt::AssimpLoader loader;

    std::cout << "Loading scene " << argv[1] << "..." << std::endl;
    if (!loader.LoadFile(argv[1])) {
        std::cerr << "Failed to load file. May have failed to "
                     "find it or it was not an .obj file." << std::endl;
        return 1;
    }

    rt::Engine engine = rt::Engine(loader);
    rt::Vector2<unsigned int> res = engine.GetRes();
    rt::Dispatcher dispatcher(engine, res);
    dispatcher.Start(); //Start to dispatch
    if (argc == 4 && std::strcmp(argv[2], "--output-image") == 0) {
        std::size_t num_frames = std::stoul(argv[3]);
        while (dispatcher.GetNumberOfProcessed() < num_frames) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            dispatcher.Flush();
        }
        dispatcher.Stop();
        bitmap_image bitmap(res.X, res.Y);
        std::vector<rt::Color> const& image = dispatcher.Flush();
        std::size_t i = 0;
        std::size_t size = res.Y * res.X;
        while (i < size) {
            bitmap.set_pixel(i % res.X, i / res.Y, image[i].GetColor().rgba.r, image[i].GetColor().rgba.g, image[i].GetColor().rgba.b);
            i++;
        }
        bitmap.save_image("output.bpm");
    } else {
        sf::RenderWindow window(sf::VideoMode(res.X, res.Y), "RayTracer 2.0");
        window.setFramerateLimit(144);
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
                    window.close();
                    dispatcher.Stop();
                }
            }
        }
    }
    return 0;
}
