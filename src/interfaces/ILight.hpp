/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 25/04/25.                                          
**         |___/ 
*/

#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include "my.hpp"


class ILight {
    public:
    virtual ~ILight() = default;

    virtual Vecteur getDirectionFrom(const Point& point) const = 0;
    virtual Color getIntensityAt(const Point& point) const = 0;
};



#endif //ILIGHT_HPP
