/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 29/04/25.                                          
**         |___/ 
*/

#include "Factory.hpp"

#include <ranges>
#include <Sphere.hpp>

Factory::Factory()
{
    registerPrimitive("sphere", [](dataPrimitive data, std::string name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<Sphere>(data, name);
    });
}


void Factory::registerPrimitive(const std::string& name, const Primitives_func& func) {
        primitivesCreator[name] = func;
}

void Factory::unregisterPrimitive() {
    primitivesCreator.clear();
}

Factory::~Factory() {
    unregisterPrimitive();
}

void Factory::registerLight(const std::string& name, const Lights_func& func) {
    lightsCreator[name] = func;
}

std::shared_ptr<IPrimitive> Factory::Primitive(const std::string& name, dataPrimitive& data) {
    if (!primitivesCreator.contains(name)) {
        return nullptr;
    }
    return primitivesCreator[name](data, name);
}

std::shared_ptr<ILight> Factory::Light(const std::string& name) {
    if (!lightsCreator.contains(name)) {
        return nullptr;
    }
    return lightsCreator[name]();
}