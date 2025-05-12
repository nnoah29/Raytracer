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

Raytracer::Raytracer(const Scene& scene, Render& render) : _scene(scene), _render(render) {}

void Raytracer::render()
{
    for (int j = 0; j < _render.height; j++) {
        for (int i = 0; i < _render.width; i++) {
            Color color(0, 0, 0);
            for (int s = 0; s < sample_per_pixel; s++) {
                Ray r = _scene.camera.generateRay(i, j);
                color += traceRay(r, 10);
            }
            _render.draw_pixel(i, j, color);
        }
    }
    _render.draw("exemple");
    _render.display();
}

Color Raytracer::traceRay(const Ray& ray, int depth)
{
    (void)depth;
    (void)ray;
    sample_per_pixel = 10;
    return {0.0f, 0.0f, 0.0f};
}



