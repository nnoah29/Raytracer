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
#include <memory>
#include <vector>

#include "Camera.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"

using Objs = std::vector<std::shared_ptr<IPrimitive>>;
using Light = std::vector<std::shared_ptr<ILight>>;

class Scene {
    Objs objs;
    Light lights;
    Camera camera;

    void loadObjects(const TabDataPrimitives& ps);
    void loadLights(const TabDataLights& ls);

public:
    Scene(const std::shared_ptr<dataCamera>& c, const TabDataPrimitives& ps, const TabDataLights& ls);
};



#endif //SCENE_HPP
