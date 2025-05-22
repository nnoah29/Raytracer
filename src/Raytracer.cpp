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

#include <thread>
#include <vector>
#include <sstream>
#include <mutex>
#include <fstream>
#include <iostream>
bool antialiasing = false;


Raytracer::Raytracer(Scene& scene, Render& render) : _scene(scene), _render(render)
{
    if (!antialiasing)
        sample_per_pixel = 1;
}

void Raytracer::render() const
{
    const std::vector<sf::Uint8> pixels = render_core();

    std::ofstream out(_render.filepath);
    if (!out.is_open()) throw std::runtime_error("Could not open file.");
    out << "P3\n" << _render.width << ' ' << _render.height << "\n255\n";

    for (size_t i = 0; i < pixels.size(); i += 4) {
        out << static_cast<int>(pixels[i + 0]) << " "
            << static_cast<int>(pixels[i + 1]) << " "
            << static_cast<int>(pixels[i + 2]) << "\n";
    }
    out.close();
    Render::display(pixels, _render.width, _render.height);
}

std::vector<sf::Uint8> Raytracer::render_core() const
{
    std::vector<std::stringstream> buffers(NB_THREADS);
    std::vector<std::thread> threads;
    const int lines_per_thread = _render.height / NB_THREADS;
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
                    color += traceRay(r, 10);
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
    threads.clear();

    std::vector<sf::Uint8> pixels;
    for (auto& buf : buffers) {
        int r, g, b;
        while (buf >> r >> g >> b) {
            pixels.push_back(static_cast<sf::Uint8>(r));
            pixels.push_back(static_cast<sf::Uint8>(g));
            pixels.push_back(static_cast<sf::Uint8>(b));
            pixels.push_back(255);
        }
        buf.str("");
        buf.clear();
    }
    return pixels;
}

void Raytracer::handleKeyCode(sf::RenderWindow &window, const sf::Event& event) const
{
    if (event.type != sf::Event::KeyPressed)
        return;
    switch (event.key.code) {
        case sf::Keyboard::Escape: window.close(); break;
        case sf::Keyboard::Right : _scene.camera.position.x -= 0.1; break;
        case sf::Keyboard::Left : _scene.camera.position.x += 0.1; break;
        case sf::Keyboard::Down : _scene.camera.position.z -= 0.1; break;
        case sf::Keyboard::Up : _scene.camera.position.z += 0.1; break;
    default: ;
    }
}

void Raytracer::renderLive() const
{
    sf::RenderWindow window(sf::VideoMode(_render.width/2, _render.height/2), _render.filepath, sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Texture texture;
    sf::Event event{};
    texture.create(_render.width, _render.height);

    while (window.isOpen()){
        std::vector<sf::Uint8> pixels = render_core();
        texture.update(pixels.data());
        sf::Sprite sprite(texture);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            handleKeyCode(window, event);
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}


Color Raytracer::traceRay(const Ray& ray, int depth) const
{
    // if (depth <= 0)
    //     return {0, 0, 0};
    (void)depth;
    PointOfImpact point;
    if (_scene.hit(ray, 0.001f, std::numeric_limits<float>::infinity(), point)) {
        const Color local_color = point.material.color;
        // if (depth > 0 && point.material.reflectivity > 0.0f) {
        // const Vecteur view_dir = -ray.direction().normalized();
        // const Vecteur reflect_dir = Scene::reflect(view_dir, point.normal);
        // const Ray reflected_ray(point.p + point.normal * 0.001f, reflect_dir);
        // const Color reflected_color = traceRay(reflected_ray, depth - 1);
        //
        // return local_color + reflected_color * point.material.reflectivity;
        // }
        return local_color;
    }
    const Vecteur unit_direction = ray.direction().normalized();
    const auto a = 0.5*(unit_direction.y + 1.0);
    return (Color(1.0, 1.0, 1.0)* (1.0-a)) + (Color(0.5, 0.7, 1.0) * a) * _scene.ambient_intensity;
}
