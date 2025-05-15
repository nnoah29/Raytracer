/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-noah.toffa
** File description:
** Cylinder.hpp
*/

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "APrimitive.hpp"

class Cylinder final: public APrimitive {
public:
    Cylinder(dataPrimitive& data, const std::string& name);

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const override;
};

#endif // CYLINDER_HPP