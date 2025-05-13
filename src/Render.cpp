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

#include "conf.hpp"


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

    const int r_byte = static_cast<int>(256 * clamp(r));
    const int g_byte = static_cast<int>(256 * clamp(g));
    const int b_byte = static_cast<int>(256 * clamp(b));

    out << r_byte << " " << g_byte << " " << b_byte << "\n";
}


void Render::display() {
    if (!texture.loadFromFile(filepath)) {
        std::cerr << "Failed to load texture from image!" << std::endl;
        return;
    }
    sprite.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(width, height), "Ray Traced Image");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
}
