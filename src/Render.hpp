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

#ifndef RENDER_HPP
#define RENDER_HPP
#include <SFML/Graphics.hpp>
#include "../includes/Color.hpp"

class Render {
    private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string path;

    public:
    int width, height;
    Render(int width, int height);

    void draw_pixel(int i, int j, const Color& c);
    void draw(const std::string& filename);
    void display();
};



#endif //RENDER_HPP
