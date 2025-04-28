/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 24/04/25.                                          
**         |___/ 
*/

#ifndef ICAMERA_HPP
#define ICAMERA_HPP
#include "../../includes/Ray.hpp"
#include "../../includes/Vecteur.hpp"

typedef struct Resolution {
    int width;
    int height;

    Resolution(int width, int height) : width(width), height(height) {}
    Resolution() : width(0), height(0) {}
} Resolution;


class ICamera {
    public:
    virtual ~ICamera() = default;

    virtual Resolution getResolution() const = 0;
    virtual Vecteur getPosition() const = 0;
    virtual Vecteur getRotation() const = 0;
    virtual float getFOV() const = 0;

    virtual void setRotation(const Vecteur& rotation) = 0;
    virtual void setPosition(const Vecteur& position) = 0;
    virtual void setResolution(int width, int height) = 0;
    virtual void setFOV(float fov) = 0;
};



#endif //ICAMERA_HPP
