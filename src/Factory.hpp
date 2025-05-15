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

#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "APrimitive.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"


class Factory {
private:
    using Primitives_func = std::function< std::shared_ptr<IPrimitive>(dataPrimitive data, const std::string& name) > ;
    using Lights_func = std::function< std::shared_ptr<ILight>(dataLight data, const std::string& name) > ;
    std::map<std::string, Primitives_func> primitivesCreator;
    std::map<std::string, Lights_func> lightsCreator;

public:
    Factory();
    ~Factory();

    void registerPrimitive(const std::string& name, const Primitives_func& func);
    void registerLight(const std::string& name, const Lights_func& func);
    void unregisterPrimitive();
    std::shared_ptr<IPrimitive> Primitive(const std::string& name, dataPrimitive& data);
    std::shared_ptr<ILight> Light(const std::string& name, dataLight& data);
};

#endif //FACTORY_HPP
