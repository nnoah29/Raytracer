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

    static Vecteur reflect(const Vecteur& v, const Vecteur& n);

    void determine_color(PointOfImpact& p) const;
    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact& p) const;
};



#endif //SCENE_HPP
