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

#include "Raytracer.hpp"

#include <fstream>
#include <iostream>

Raytracer::Raytracer(const Scene& scene, Render& render) : _scene(scene), _render(render) {}

void Raytracer::render()
{
    std::cout << _render.filepath << std::endl;
    std::ofstream out(_render.filepath);

    if (!out.is_open()) throw std::runtime_error("Could not open file.");
    out << "P3\n" << _render.width << ' ' << _render.height << "\n256\n";

    for (int j = 0; j < _render.height; j++) {
        std::clog << "\rLines remaining: " << (_render.height - j - 1) << ' ' << std::flush;
        for (int i = 0; i < _render.width; i++) {

            Color color(0, 0, 0);
            for (int s = 0; s < sample_per_pixel; s++) {
                Ray r = _scene.camera.generateRay(i, j);
                color += traceRay(r, LIGHT_DEPTH);
            }
            _render.draw_pixel(out, color);
        }
    }
    out.close();

    //_render.display();
}

Vecteur unit_vector(const Vecteur& v) {
    return v / v.length();
}


Color Raytracer::traceRay(const Ray& ray, int depth)
{
    (void)depth;
    sample_per_pixel = 10;
    PointOfImpact point;
    if (_scene.hit(ray, 0.001f, std::numeric_limits<float>::infinity(), point)) {
        return {0.5f, 0.5f, 0.0f};
    }

    const Vecteur unit_direction = unit_vector(ray.direction());
    const auto a = 0.5*(unit_direction.y + 1.0);
    return (Color(1.0, 1.0, 1.0)* (1.0-a)) + (Color(0.5, 0.7, 1.0) * a);
}



