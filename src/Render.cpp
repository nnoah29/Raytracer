/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 28/04/25.                                          
**         |___/ 
*/

#include "Render.hpp"
#include <iostream>
#include <valarray>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "conf.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


bool Render::loadPPM_P3(const std::string& filename, std::vector<sf::Uint8>& pixels, unsigned& width, unsigned& height)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier PPM.\n";
        return false;
    }
    std::string line, magic;
    std::getline(file, magic);
    while (std::getline(file, line)) {
        if (line[0] != '#') break;
    }
    std::istringstream iss(line);
    iss >> width >> height;
    int maxVal = 0;
    file >> maxVal;
    int r, g, b;
    pixels.reserve(width * height * 4);
    while (file >> r >> g >> b) {
        pixels.push_back(static_cast<sf::Uint8>(r));
        pixels.push_back(static_cast<sf::Uint8>(g));
        pixels.push_back(static_cast<sf::Uint8>(b));
        pixels.push_back(255);
    }
    if (pixels.size() != width * height * 4) {
        std::cerr << "Erreur : nombre de pixels incorrect.\n";
        return false;
    }
    return true;
}

Render::Render(int width, int height, const std::string& filename) : width(width), height(height) {
    filepath = SCREENSHORT_DIR + filename + ".ppm";
}

float linearing(float x)
{
    if (x > 0)
        return std::sqrt(x);
    return 0;
}

void Render::draw_pixel(std::ostream& out, const Color& c) {

    auto clamp = [](float x) {
        if (x < 0.0f) return 0.0f;
        if (x > 1.0f) return 1.0f;
        return x;
    };
    const auto r = linearing(c.r);
    const auto g = linearing(c.g);
    const auto b = linearing(c.b);

    const int r_byte = static_cast<int>(255.0f * clamp(r)); // +0.5f pour arrondir correctement
    const int g_byte = static_cast<int>(255.0f * clamp(g));
    const int b_byte = static_cast<int>(255.0f * clamp(b));
    out << r_byte << " " << g_byte << " " << b_byte << "\n";
}

void Render::display(std::vector<sf::Uint8> pixels, unsigned width, unsigned height)
{
    sf::RenderWindow window(sf::VideoMode(width/2, height/2), "Ratracing", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Texture texture;
    texture.create(width, height);
    texture.update(pixels.data());
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Space))){
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

