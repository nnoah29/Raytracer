/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-noah.toffa
** File description:
** Cone.hpp
*/

#ifndef CONE_HPP
#define CONE_HPP

#include "APrimitive.hpp"

class Cone final: public APrimitive {
public:
    Cone(dataPrimitive& data, const std::string& name);
    Point apex;
    Point axis;

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const override;
};

#endif // CONE_HPP