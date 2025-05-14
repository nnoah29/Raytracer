/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-noah.toffa
** File description:
** Plane.hpp
*/


#ifndef PLANE_HPP
#define PLANE_HPP

#include "APrimitive.hpp"

class Plane final: public APrimitive {
public:
    Plane(dataPrimitive& data, const std::string& name);

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const override;
};

#endif // PLANE_HPP