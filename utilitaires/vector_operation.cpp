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

#include "../includes/Vecteur.hpp"

Vecteur operator+(const Vecteur& v1, const Vecteur& v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vecteur operator-(const Vecteur& v1, const Vecteur& v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vecteur operator*(const Vecteur& v1, const Vecteur& v2) {
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

Vecteur operator*(const Vecteur& v1, float t) {
    return {v1.x * t, v1.y * t, v1.z * t};
}

Vecteur operator*(float t, const Vecteur& v1) {
    return {v1.x * t, v1.y * t, v1.z * t};
}

Vecteur operator/(const Vecteur& v1, float t) {
    return (1 / t) * v1;
}

double dot(const Vecteur& v1, const Vecteur& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vecteur cross(const Vecteur& v1, const Vecteur& v2) {
    return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

Vecteur unitVector(const Vecteur& v) {
    return v / v.length();
}

