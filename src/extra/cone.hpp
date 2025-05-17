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

#ifndef CONE_HPP
#define CONE_HPP

#include "APrimitive.hpp"

class cone final: public APrimitive {
public:
    cone(dataPrimitive& data, const std::string& name);

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const override;
};

#endif // CONE_HPP
