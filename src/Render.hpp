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
    static bool loadPPM_P3(const std::string& filename, std::vector<sf::Uint8>& pixels, unsigned& width, unsigned& height);


    public:
    std::string filepath;
    int width, height;
    Render(int width, int height, const std::string& filename);

    static void draw_pixel(std::ostream& out, const Color& c);
    static void display(std::vector<sf::Uint8> pixels, unsigned width, unsigned height) ;
};



#endif //RENDER_HPP
