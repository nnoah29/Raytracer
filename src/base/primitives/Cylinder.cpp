/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-noah.toffa
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"

Cylinder::Cylinder(dataPrimitive& data, const std::string& name): APrimitive(data, name) {}

bool Cylinder::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const {
    Vecteur o = ray.origin();
    Vecteur d = ray.direction();

    float dx = d.x, dy = d.y;
    float ox = o.x, oy = o.y;

    float A = dx*dx + dy*dy;
    float B = 2 * (dx*ox + dy*oy);
    float C = ox*ox + oy*oy - data.radius * data.radius;

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
    v.z = 0;
    p.set_face_normal(ray, v.normalized());

    return true;
}