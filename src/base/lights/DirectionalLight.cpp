/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 14/05/25.                                          
**         |___/ 
*/

#include "DirectionalLight.hpp"

#include <iostream>


Vecteur DirectionalLight::getDirectionFrom(const Point& point) const {
    (void)point;
    return  data.direction;
}

Color DirectionalLight::getIntensityAt(const PointOfImpact& point) const {
    const Vecteur direction = getDirectionFrom(point.p).normalized();
    const float diff = std::max(dot(point.normal, direction), 0.0f);

    return point.material.color * diff;
}