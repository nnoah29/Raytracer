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


class Raytracer {
    public:
    Raytracer(const Scene& scene, Render& render);

    void render();

private:
    const Scene& _scene;
    Render& _render;

    Color traceRay(const Ray& ray, int depth = 0);
    bool hitAnything(const Ray& ray, float t_min, float t_max, PointOfImpact& rec);
};




#endif //RAYTRACER_HPP
