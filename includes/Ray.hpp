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

#ifndef RAY_HPP
#define RAY_HPP
#include "Vecteur.hpp"


class Ray {
private:
    Point _origin;
    Vecteur _direction;
public:
    Ray(const Vecteur& origin, const Vecteur& direction) : _origin(origin), _direction(direction.normalized()) {}
    Ray() : _origin(Point(0,0,0)), _direction(Vecteur(1,0,0)) {}


    const Point& origin() const { return _origin; }
    const Vecteur& direction() const { return _direction; }

    Point at(float t) const {
        return _origin + _direction * t;
    }
};


#endif //RAY_HPP
