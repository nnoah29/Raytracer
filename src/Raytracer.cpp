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


#include <thread>
#include <vector>
#include <sstream>
#include <mutex>

void Raytracer::render() const
{
    std::vector<std::stringstream> buffers(NB_THREADS);
    std::vector<std::thread> threads;
    int lines_per_thread = _render.height / NB_THREADS;

    std::atomic<int> lines_done(0);

    auto render_part = [&](int thread_id, int start_y, int end_y) {
        std::stringstream& out = buffers[thread_id];
        for (int j = start_y; j < end_y; ++j) {
            const int remaining = _render.height - ++lines_done;
            std::clog << "\rLines remaining: " << remaining << std::flush;
            for (int i = 0; i < _render.width; ++i) {
                Color color(0, 0, 0);
                for (int s = 0; s < sample_per_pixel; s++) {
                    Ray r = _scene.camera.generateRay(i, j);
                    color += traceRay(r, LIGHT_DEPTH);
                }
                color = color / static_cast<float>(sample_per_pixel);
                Render::draw_pixel(out, color);
            }
        }
    };

    for (int t = 0; t < NB_THREADS; ++t) {
        int start = t * lines_per_thread;
        int end = (t == NB_THREADS - 1) ? _render.height : start + lines_per_thread;
        threads.emplace_back(render_part, t, start, end);
    }

    for (auto& th : threads)
        th.join();

    std::ofstream out(_render.filepath);
    if (!out.is_open()) throw std::runtime_error("Could not open file.");
    out << "P3\n" << _render.width << ' ' << _render.height << "\n255\n";

    for (auto& buf : buffers)
        out << buf.str();

    out.close();
    std::clog << "\rDone.                       \n" << std::flush;
    _render.display();
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

    const Vecteur unit_direction = unit_vector(ray.direction());
    const auto a = 0.5*(unit_direction.y + 1.0);
    return (Color(1.0, 1.0, 1.0)* (1.0-a)) + (Color(0.5, 0.7, 1.0) * a) * _scene.ambient_intensity;
}



