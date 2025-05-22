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

bool Cylinder::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const {
    const Vecteur origin = ray.origin() - data.position;
    const Vecteur direction = ray.direction();

    const float a = direction.x * direction.x + direction.y * direction.y;
    const float b = 2.0f * (origin.x * direction.x + origin.y * direction.y);
    const float c = origin.x * origin.x + origin.y * origin.y - data.radius * data.radius;

    const float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    const float sqrtD = std::sqrt(discriminant);
    float t = (-b - sqrtD) / (2 * a);
    if (t < t_min || t > t_max) {
        t = (-b + sqrtD) / (2 * a);
        if (t < t_min || t > t_max)
            return false;
    }

    const Vecteur hit = ray.at(t);
    float z_local = hit.z - data.position.z;
    if (z_local < 0 || z_local > data.height)
        return false;

    Vecteur normal = hit - data.position;
    normal.z = 0;
    normal = normal.normalized();

    p.t = t;
    p.p = hit;
    p.set_face_normal(ray, normal);
    p.material = data.material;
    return true;
}

extern "C" void RegisterPlugin(Factory* f) {
    f->registerPrimitive("cylinders", [](dataPrimitive data, const std::string& name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<Cylinder>(data, name);
    });
}