/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 01/05/25.                                          
**         |___/ 
*/

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include "Color.hpp"
#include "Ray.hpp"
#include "Render.hpp"
#include "Scene.hpp"


    using pixel_buffer = std::pair<std::vector<sf::Uint8>, std::vector<std::stringstream>>;
class Raytracer {
    public:

    Raytracer(Scene& scene, Render& render);

    void render() const;
    std::vector<sf::Uint8> render_core() const;
    void handleKeyCode(sf::RenderWindow& window, const sf::Event& event) const;
    void renderLive() const;

private:
    Scene& _scene;
    Render& _render;
    int sample_per_pixel = 10;




    Color traceRay(const Ray& ray, int depth = 0) const;
};




#endif //RAYTRACER_HPP
