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

}

Color Raytracer::traceRay(const Ray& ray, int depth)
{
    (void)depth;
    (void)ray;
    return {0.0f, 0.0f, 0.0f};
}

bool Raytracer::hitAnything(const Ray& ray, float t_min, float t_max, PointOfImpact& rec)
{
    (void)ray;
    (void)t_min;
    (void)t_max;
    (void)rec;
    return true;
}


