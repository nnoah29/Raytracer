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
    float ambient_intensity{};
    float diffuse_intensity{};
    Camera camera;
    Scene(const std::shared_ptr<dataCamera>& c, const TabDataPrimitives& ps, const TabDataLights& ls, const Factory& f);

    static Vecteur reflect(const Vecteur& v, const Vecteur& n) {
        return v - (n * 2 * dot(v, n));
    }

    void determine_color(PointOfImpact& p) const {
        const Color ambient = p.material.color * ambient_intensity;
        Color diffuse{0.0f, 0.0f, 0.0f};
        Color specular{0.0f, 0.0f, 0.0f};

        for (const auto& l : lights) {
            bool blocked = false;
            Color intensity = l->getIntensityAt(p);
            Vecteur light_dir = l->getDirectionFrom(p.p);
            const float light_distance = light_dir.length();
            light_dir = light_dir.normalized();

            Ray shadow_ray(p.p + (p.normal * 0.01f), light_dir);
            PointOfImpact shadow_poi;
            for (const auto& obj : objs) {
                if (obj->hit(shadow_ray, 0.01f, light_distance, shadow_poi)) {
                    blocked = true;
                    break;
                }
            }
            if (!blocked) {
                diffuse += intensity * diffuse_intensity;

                if (p.material.shininess_is_define) {
                    Vecteur view_dir = (camera.getPosition() - p.p).normalized();
                    Vecteur reflect_dir = reflect(-light_dir, p.normal);
                    const float spec = std::pow(std::max(dot(view_dir, reflect_dir), 0.0f), p.material.shininess);
                    specular += Color(1.0f, 1.0f, 1.0f) * 0.5f * spec;
                }
            }
        }
        p.material.color = diffuse + ambient + specular;
    }


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
                determine_color(p);
            }
        }
        if (hit_anything) {
            determine_color(p);
        }
        return hit_anything;
    }
};



#endif //SCENE_HPP
