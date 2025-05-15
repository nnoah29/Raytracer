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

#include "PointLight.hpp"

Vecteur PointLight::getDirectionFrom(const Point& point) const {
    return (data.position - point).normalized();
}

Color PointLight::getIntensityAt(const Point& point) const {
    const float distance = (data.position - point).lengthSquared();
    return data.intensity / static_cast<float>(4.0f * M_PI * distance);
}