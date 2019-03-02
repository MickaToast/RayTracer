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
#include "Loader/AssimpLoader.h"
#include "Camera/Camera.h"
#include "Engine/Engine.h"
#include "Dispatcher/Dispatcher.h"
#include "Vector/Vector2.h"
#include "Config/Config.h"

void exportToImage(rt::Dispatcher &dispatcher, std::size_t num_frames, rt::Vector2<unsigned int> const& res) {
    while (dispatcher.GetNumberOfProcessed() < num_frames) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    dispatcher.Stop();

    sf::Image export_image;
    export_image.create(res.X, res.Y);
    std::vector<rt::Color> const& image = dispatcher.Flush();
    std::size_t i = 0;
    std::size_t size = res.Y * res.X;
    while (i < size) {
        export_image.setPixel(i % res.X, i / res.X, sf::Color(image[i].GetColor().rgba.r, image[i].GetColor().rgba.g, image[i].GetColor().rgba.b));
        i++;
    }
    export_image.saveToFile("output.bmp");
}

void displayToScreen(rt::Dispatcher &dispatcher, rt::Vector2<unsigned int> const& res) {
    sf::RenderWindow window(sf::VideoMode(res.X, res.Y), "RayTracer 2.0");
    window.setFramerateLimit(1); // Keep to 1 in order to avoid using thread for displaying
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
            if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
                dispatcher.Stop();
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " scene.dae <options>" << std::endl;
        std::cerr << "Possible options: --background-image=<path> --output-image=<number>" << std::endl;
        return 1;
    }

    rt::AssimpLoader loader;

    std::cout << "Loading scene " << argv[1] << "..." << std::endl;
    if (!loader.LoadFile(argv[1])) {
        return 1;
    }

    rt::Config config;
    config.LoadFromArguments(argc, argv);
    rt::Engine engine = rt::Engine(loader);

    if (config.RequestBackground()) {
        sf::Image skyTexture;
        if (skyTexture.loadFromFile(config.GetBackgroundPath())) {
            engine.SetBackground(std::shared_ptr<rt::Sky>(new rt::SphereSky(rt::Vector2<unsigned int>(skyTexture.getSize().x, skyTexture.getSize().y), skyTexture.getPixelsPtr())));
        } else {
            std::cerr << "Warning: Could not load background " << config.GetBackgroundPath() << std::endl;
        }
    }

    rt::Vector2<unsigned int> res = engine.GetRes();
    rt::Dispatcher dispatcher(engine, res);
    dispatcher.Start(); //Start to dispatch

    if (config.RequestImageOutput()) {
        exportToImage(dispatcher, config.GetImageOutputFrames(), res);
    } else {
        displayToScreen(dispatcher, res);
    }
    return 0;
}
