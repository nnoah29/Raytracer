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

#ifndef SCENE_HPP
#define SCENE_HPP
#include <iostream>
#include <memory>
#include <vector>

#include "Camera.hpp"
#include "Factory.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"

using Objs = std::vector<std::shared_ptr<IPrimitive>>;
using Light = std::vector<std::shared_ptr<ILight>>;

class Scene {
    Objs objs;
    Light lights;
    Factory factory;

    void loadObjects(const TabDataPrimitives& ps);
    void loadLights(const TabDataLights& ls);

public:
    float ambient_intensity;
    float diffuse_intensity;
    Camera camera;
    Scene(const std::shared_ptr<dataCamera>& c, const TabDataPrimitives& ps, const TabDataLights& ls, const Factory& f);

    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const
    {
        PointOfImpact p_temps;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& obj : objs) {
            if (obj->hit(ray, t_min, closest_so_far, p_temps)) {
                hit_anything = true;
                closest_so_far = p_temps.t;
                p = p_temps;
            }
        }
        return hit_anything;
    }
};



#endif //SCENE_HPP
