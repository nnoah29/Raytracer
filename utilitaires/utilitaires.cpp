/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 26/04/25.                                          
**         |___/ 
*/


#include "../includes/Ray.hpp"
#include "../includes/Vecteur.hpp"

/// fonction pour déterminer si un rayon touche une sphère
bool hit_sphere(const Point& center, double radius, const Ray& r) {
    const Vecteur oc = center - r.origin();
    const auto a = Vecteur::dot(r.direction(), r.direction());
    const auto b = -2.0 * Vecteur::dot(r.direction(), oc);
    const auto c = Vecteur::dot(oc, oc) - radius*radius;
    const auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}



// for (int i = 0; i <= 10000; ++i) {
//         std::cout << "\r\33[2K" << "ok(" << i << ")" << std::flush; // Affiche sur la même ligne
//         std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause plus rapide
//     }

#include "../src/Factory.hpp"
#include "Sphere.hpp" // ta primitive concrète

extern "C" void RegisterPlugin(Factory* f) {
    f->registerPrimitive("nom de la primitives", [](dataPrimitive data, std::string name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<Sphere>(data, name); // Sphere est un exemple
    });
}

