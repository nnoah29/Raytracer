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
