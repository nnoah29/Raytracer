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

#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <iostream>

#include "APrimitive.hpp"


class Sphere final : public APrimitive {

    public:
    Sphere(dataPrimitive& data, const std::string& name): APrimitive(data, name){}

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const override
    {
        const Point oc = data.position - ray.origin();
        const auto a = ray.direction().lengthSquared();
        const auto b = dot(ray.direction(), oc);
        const auto c = oc.lengthSquared() - data.radius * data.radius;

        //std::cout << a << " " << b << " " << c << std::endl;
        const auto discriminant = b * b - a * c;
        if (discriminant < 0) {
            return false;
        }

        const auto sqrt_discriminant = std::sqrt(discriminant);

        auto root = (b - sqrt_discriminant) / a;
        if (!surrounds(t_min, root, t_max)) {
            root = (b + sqrt_discriminant) / a;
            if (!surrounds(t_min, root, t_max))
                return false;
        }

        p.t = root;
        p.p = ray.at(p.t);
        const Vecteur out_normal = (p.p - data.position) / data.radius;
        p.set_face_normal(ray, out_normal);
        return true;
    }
};



#endif //SPHERE_HPP
