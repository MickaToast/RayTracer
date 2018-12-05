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

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage 1: " << argv[0] << " scene.obj" << std::endl;
        std::cerr << "Usage 2: " << argv[0] << " scene.obj 1980x1080" << std::endl;
        std::cerr << "Usage 3: " << argv[0] << " scene.obj 1980x1080 --output-image 5" << std::endl;
        return 1;
    }

    rt::AssimpLoader loader;

    std::cout << "Loading scene " << argv[1] << "..." << std::endl;
    if (!loader.LoadFile(argv[1])) {
        std::cerr << "Failed to load file. May have failed to "
                     "find it or it was not an .obj file." << std::endl;
        return 1;
    }

    rt::Vector2<unsigned int> res(1600, 900);
    if (argc >= 3) {
        std::string s{argv[2]};
        std::regex regex{R"([\sx]+)"};
        std::sregex_token_iterator it{s.begin(), s.end(), regex, -1};
        std::vector<std::string> split{it, {}};
        res.X = std::stoul(split[0]);
        res.Y = std::stoul(split[1]);
    }
    /*
    //Salle de bain
    rt::Vector3<float> camPos = rt::Vector3<float>(10, 20, 30);    
    rt::Vector3<float> camTarget = rt::Vector3<float>(-10, 0, 0);    
    */
    /*
    //Hourglass
    rt::Vector3<float> camPos = rt::Vector3<float>(5, 3, 5);    
    rt::Vector3<float> camTarget = rt::Vector3<float>(0, 2, 0);    
    */
    /*
    //Dragon
    rt::Vector3<float> camPos = rt::Vector3<float>(-1, .5, 0);    
    rt::Vector3<float> camTarget = rt::Vector3<float>(0, 0, 0);    
    */
    /*
    //Sport car
    rt::Vector3<float> camPos = rt::Vector3<float>(3, 1.5, 3);    
    rt::Vector3<float> camTarget = rt::Vector3<float>(0, 0, 0);    
    */
    /*
    //Al
    rt::Vector3<float> camPos = rt::Vector3<float>(0, 0, 8);    
    rt::Vector3<float> camTarget = rt::Vector3<float>(0, 0, -1);    
    */
    
    //Cornell
    rt::Vector3<float> camPos = rt::Vector3<float>(0, .5, 1.8);    
    rt::Vector3<float> camTarget = rt::Vector3<float>(0, .5, 0);    
    
    rt::Dispatcher dispatcher(rt::Engine(loader, rt::Camera(camPos, camTarget, res)), res);
    dispatcher.Start(); //Start to dispatch
    if (argc == 5 && std::strcmp(argv[3], "--output-image") == 0) {
        std::size_t num_frames = std::stoul(argv[4]);
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
