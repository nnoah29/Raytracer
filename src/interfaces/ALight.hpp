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

#ifndef ALIGHT_HPP
#define ALIGHT_HPP
#include "Color.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "my.hpp"
#include "Vecteur.hpp"


class ALight : public ILight {
protected:
    dataLight data;
    std::string name;
    public:
public:
    ALight(const dataLight& _data, const std::string& _name) {
        this->data = _data;
        this->name = _name;
    };

    ~ALight() override = default;
    Vecteur getDirectionFrom(const Point& point) const override = 0;
    Color getIntensityAt(const PointOfImpact& point) const override = 0;

};



#endif //ALIGHT_HPP
