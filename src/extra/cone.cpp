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

#include "cone.hpp"
#include "../Factory.hpp"

extern "C" void RegisterPlugin(Factory* f) {
    f->registerPrimitive("cones", [](dataPrimitive data, const std::string& name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<cone>(data, name);
    });
}

cone::cone(dataPrimitive& data, const std::string& name): APrimitive(data, name) {}

bool cone::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const {

    // float k = data.radius / data.height;
    // float k2 = k * k;

    // Point normal = data.normal.normalized();
    // Vecteur o = ray.origin() - normal;    // origine relative au cône
    // Vecteur d = ray.direction();

    // float dx = d.x, dy = d.y, dz = d.z;
    // float ox = o.x, oy = o.y, oz = o.z;

    // float A = dx*dx + dy*dy - k2 * dz*dz;
    // float B = 2 * (dx*ox + dy*oy - k2 * dz*oz);
    // float C = ox*ox + oy*oy - k2 * oz*oz;

    // float discriminant = B*B - 4*A*C;
    // if (discriminant < 0)
    //     return false;

    // float sqrtD = std::sqrt(discriminant);
    // float root = (-B - sqrtD) / (2*A);
    // if (!surrounds(t_min, root, t_max)) {
    //     root = (-B + sqrtD) / (2*A);
    //     if (!surrounds(t_min, root, t_max))
    //         return false;
    // }

    // float z = ray.at(root).z - normal.z;
    // if (z < 0 || z > data.height)
    //     return false;

    // p.t = root;
    // p.p = ray.at(p.t);

    // Vecteur v = p.p - normal;
    // v.z = -k * std::sqrt(v.x*v.x + v.y*v.y);
    // p.set_face_normal(ray, v.normalized());

    // return true;


    float k = data.radius / data.height;
    float k2 = k * k;

    Vecteur o = ray.origin();
    Vecteur d = ray.direction();

    float dx = d.x, dy = d.y, dz = d.z;
    float ox = o.x, oy = o.y, oz = o.z;

    float A = dx*dx + dy*dy - k2 * dz*dz;
    float B = 2 * (dx*ox + dy*oy - k2 * dz*oz);
    float C = ox*ox + oy*oy - k2 * oz*oz;

    float discriminant = B*B - 4*A*C;
    if (discriminant < 0)
        return false;

    float squareroot = std::sqrt(discriminant);
    float root = (-B - squareroot) / (2*A);
    if (!surrounds(t_min, root, t_max)) {
        root = (-B + squareroot) / (2*A);
        if (!surrounds(t_min, root, t_max))
            return false;
    }

    float z = ray.at(root).z;
    if (z < 0 || z > data.height)
        return false;

    p.t = root;
    p.p = ray.at(p.t);

    Vecteur v = p.p;
    p.set_face_normal(ray, v.normalized());

    return true;
}