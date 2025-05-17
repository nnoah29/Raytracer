/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 28/04/25.                                          
**         |___/ 
*/

#include "Cylinder.hpp"

#include "../Factory.hpp"


Cylinder::Cylinder(dataPrimitive& data, const std::string& name): APrimitive(data, name) {}

bool Cylinder::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const
{
    Vecteur axis = data.normal.normalized();
    Vecteur x = ray.origin() - data.position;

    Vecteur d = ray.direction();
    float dv = dot(d, axis);
    float xv = dot(x, axis);

    Vecteur d_perp = d - axis * dv;
    Vecteur x_perp = x - axis * xv;

    float a = dot(d_perp, d_perp);
    float b = 2.0f * dot(d_perp, x_perp);
    float c = dot(x_perp, x_perp) - data.radius * data.radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    float sqrt_disc = std::sqrt(discriminant);
    float t = (-b - sqrt_disc) / (2 * a);
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_disc) / (2 * a);
        if (t < t_min || t > t_max)
            return false;
    }

    Vecteur hit_point = ray.at(t);

    Vecteur v = hit_point - data.position;
    float h = dot(v, axis);
    if (data.height != 0)
        if (h < 0 || h > data.height) return false;

    Vecteur normal = (v - axis * h).normalized();

    p.t = t;
    p.p = hit_point;
    p.set_face_normal(ray, normal);
    p.material = data.material;
    return true;
}

extern "C" void RegisterPlugin(Factory* f) {
    f->registerPrimitive("cylinders", [](dataPrimitive data, const std::string& name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<Cylinder>(data, name);
    });
}