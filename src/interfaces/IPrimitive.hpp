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

#ifndef IPRIMITIVE_HPP
#define IPRIMITIVE_HPP
#include "../../includes/Ray.hpp"
#include "../../includes/Vecteur.hpp"
#include "../../includes/Color.hpp"
#include "../../includes/my.hpp"

typedef struct PointOfImpact
{
    Point p;
    Vecteur normal;
    float t{};
    bool front{};
    Material material{};


    void set_face_normal(const Ray& ray, const Vecteur& outward_normal) {
        front = (ray.direction().dot(outward_normal) < 0);
        normal = front ? outward_normal : -outward_normal;
    }
} PointOfImpact;

class IPrimitive {
    public:
    virtual ~IPrimitive() = default;

    virtual bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const = 0;

};



#endif //IPRIMITIVE_HPP
