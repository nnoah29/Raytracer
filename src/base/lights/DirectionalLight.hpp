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

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP
#include "ALight.hpp"


class DirectionalLight : public  ALight {
    public:
    DirectionalLight(dataLight& data, const std::string& name) : ALight(data, name) {}

    Vecteur getDirectionFrom(const Point& point) const override;
    Color getIntensityAt(const PointOfImpact& point) const override;
};



#endif //DIRECTIONALLIGHT_HPP
