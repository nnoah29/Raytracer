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

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP
#include "ALight.hpp"


class PointLight final : public ALight{
public:
    PointLight(dataLight& data, const std::string& name) : ALight(data, name) {}

    Vecteur getDirectionFrom(const Point& point) const override;
    Color getIntensityAt(const PointOfImpact& point) const override;
};



#endif //POINTLIGHT_HPP
