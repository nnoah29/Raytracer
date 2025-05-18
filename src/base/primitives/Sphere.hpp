/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 27/04/25.                                          
**         |___/ 
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <iostream>

#include "APrimitive.hpp"


class Sphere final : public APrimitive {

    public:
    Sphere(dataPrimitive& data, const std::string& name): APrimitive(data, name){}

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const override;
};



#endif //SPHERE_HPP
