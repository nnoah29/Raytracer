/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-noah.toffa
** File description:
** Cone.cpp
*/

#include"Cone.hpp"

Cone::Cone(dataPrimitive& data, const std::string& name): APrimitive(data, name) {}

bool Cone::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const {
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