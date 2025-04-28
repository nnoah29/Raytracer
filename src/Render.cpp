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

Render::Render(int width, int height) : width(width), height(height) {
    image.create(width, height, sf::Color::Black); // Image vide noire au début
}

void Render::draw_pixel(int i, int j, const Color& c) {

    auto clamp = [](float x) {
        if (x < 0.0f) return 0.0f;
        if (x > 1.0f) return 1.0f;
        return x;
    };

    const sf::Color color(
        static_cast<sf::Uint8>(255 * clamp(c.r)),
        static_cast<sf::Uint8>(255 * clamp(c.g)),
        static_cast<sf::Uint8>(255 * clamp(c.b))
    );

    if (i >= 0 && i < width && j >= 0 && j < height)
        image.setPixel(i, height - j - 1, color);
}

void Render::draw(const std::string& filename)
{
    path = "screenshots/" + filename + ".ppm";
    if (image.saveToFile(path)) {
        std::cout << "Image saved to " << filename << std::endl;
    } else {
        std::cerr << "Failed to save image!" << std::endl;
    }
}

void Render::display() {
    if (!texture.loadFromImage(image)) {
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
