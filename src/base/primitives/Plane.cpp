/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-noah.toffa
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

#include "Plane.hpp"

Plane::Plane(dataPrimitive& data, const std::string& name): APrimitive(data, name) {}

bool Plane::hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const {
    const Vecteur normal = data.normal.normalized();
    const Vecteur reference = data.reference;

    const float discriminant = dot(normal, ray.direction());
    if (discriminant == 0.0f)
        return false;

    float t = dot(reference - ray.origin(), normal) / discriminant;

    if (!surrounds(t_min, t, t_max))
        return false;

    p.t = t;
    p.p = ray.at(t);
    p.set_face_normal(ray, normal);
    p.material = data.material;
    return true;
}