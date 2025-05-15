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

void Raytracer::render() const
{
    std::ofstream out(_render.filepath);

    if (!out.is_open()) throw std::runtime_error("Could not open file.");
    out << "P3\n" << _render.width << ' ' << _render.height << "\n255\n";

    for (int j = 0; j < _render.height; j++) {
        std::clog << "\rLines remaining: " << (_render.height - j - 1) << ' ' << std::flush;
        for (int i = 0; i < _render.width; i++) {

            Color color(0, 0, 0);
            //for (int s = 0; s < sample_per_pixel; s++) {
                Ray r = _scene.camera.generateRay(i, j);
                color += traceRay(r, LIGHT_DEPTH);
            //}
            _render.draw_pixel(out, color);
        }
    }
    std::clog << "\rDone.\n" << std::flush;
    out.close();
    //_render.display();
}

Vecteur unit_vector(const Vecteur& v) {
    return v / v.length();
}


    Color Raytracer::traceRay(const Ray& ray, int depth) const
    {
        (void)depth;
        PointOfImpact point;
        if (_scene.hit(ray, 0.001f, std::numeric_limits<float>::infinity(), point)) {
        const Color local_color = point.material.color;

        // if (depth > 0 && point.material.reflectivity > 0.0f) {
        //     const Vecteur view_dir = -ray.direction().normalized();
        //     const Vecteur reflect_dir = Scene::reflect(view_dir, point.normal);
        //     const Ray reflected_ray(point.p + point.normal * 0.001f, reflect_dir);
        //     const Color reflected_color = traceRay(reflected_ray, depth - 1);
        //
        //     return local_color * (1.0f - point.material.reflectivity) + reflected_color * point.material.reflectivity;
        // }

        return local_color;
    }
    if (_scene.hit(ray, 0.001f, std::numeric_limits<float>::infinity(), point)) {
        return point.material.color;
    }

    const Vecteur unit_direction = unit_vector(ray.direction());
    const auto a = 0.5*(unit_direction.y + 1.0);
    return (Color(1.0, 1.0, 1.0)* (1.0-a)) + (Color(0.5, 0.7, 1.0) * a) * _scene.ambient_intensity;
}



