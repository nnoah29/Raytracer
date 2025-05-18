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

#ifndef VECTEUR_HPP
#define VECTEUR_HPP
#include <cmath>



class Vecteur {
public:
    float x, y, z;

    Vecteur() : x(0), y(0), z(0) {}
    Vecteur(float x, float y, float z) : x(x), y(y), z(z) {}

    // Opérateurs usuels
    Vecteur operator+(const Vecteur& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vecteur operator-(const Vecteur& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vecteur operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    Vecteur operator-() const { return {-x, -y, -z}; }

    float dot(const Vecteur& v) const { return x * v.x + y * v.y + z * v.z; }

    static float dot(const Vecteur& v1, const Vecteur& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    Vecteur normalized() const {
        const float len = std::sqrt(x * x + y * y + z * z);
        return (len > 0) ? (*this * (1.0f / len)) : Vecteur(0, 0, 0);
    }

    float lengthSquared() const {
        return x * x + y * y + z * z;
    }

    float length() const {
        return std::sqrt(lengthSquared());
    }
};

using Point = Vecteur;


#endif //VECTEUR_HPP
