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
        std::clog << "\rScanlines remaining: " << (_render.height - j - 1) << ' ' << std::flush;
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

    _render.display();
}

Color Raytracer::traceRay(const Ray& ray, int depth)
{
    (void)depth;
    (void)ray;
    sample_per_pixel = 10;
    return {1.0f, 0.0f, 0.0f};
}



