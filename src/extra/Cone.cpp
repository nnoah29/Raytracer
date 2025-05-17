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

#include "Cone.hpp"
#include "../Factory.hpp"


Cone::Cone(dataPrimitive& data, const std::string& name): APrimitive(data, name) {}

bool Cone::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const
{
    const Vecteur axis = data.normal.normalized();
    const Vecteur x = ray.origin() - data.position;

    const float k = std::tan(data.corner);
    const float k2 = k * k;

    const Vecteur d = ray.direction();
    const float dv = dot(d, axis);
    const float xv = dot(x, axis);

    const float a = dot(d, d) - k2 * dv * dv;
    const float b = 2.0f * (dot(d, x) - k2 * dv * xv);
    const float c = dot(x, x) - k2 * xv * xv;

    const float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    float sqrt_disc = std::sqrt(discriminant);
    float t = (-b - sqrt_disc) / (2 * a);
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_disc) / (2 * a);
        if (t < t_min || t > t_max)
            return false;
    }

    const Vecteur hit_point = ray.at(t);

    const Vecteur apex_to_hit = hit_point - data.position;
    const float h = dot(apex_to_hit, axis);
    if (data.height != 0)
        if (h < 0 || h > data.height) return false;

    const Vecteur normal = (apex_to_hit - axis * h).normalized();

    p.t = t;
    p.p = hit_point;
    p.set_face_normal(ray, normal);
    p.material = data.material;
    return true;
}

extern "C" void RegisterPlugin(Factory* f) {
    f->registerPrimitive("cones", [](dataPrimitive data, const std::string& name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<Cone>(data, name);
    });
}
