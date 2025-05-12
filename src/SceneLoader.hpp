/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 28/04/25.                                          
**         |___/ 
*/

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <libconfig.h++>
#include <iostream>
#include <filesystem>
#include "Scene.hpp"


class SceneLoader {
private:
    std::shared_ptr<dataCamera> c = std::make_shared<dataCamera>(0.0);
    std::vector<std::shared_ptr<dataPrimitive>> ps;
    std::vector<std::shared_ptr<dataLight>> ls;
    libconfig::Config cfg;
    float ambient_intensity;
    float diffuse_intensity;

    void loadCamera(const libconfig::Setting& camera) const;
    void loadPrimitives(const libconfig::Setting& primitives);
    void loadLights(const libconfig::Setting& light);
public:
    SceneLoader(const std::string& path, int ac);

    Scene createScene(Factory& f) const;
};



#endif //SCENELOADER_HPP
