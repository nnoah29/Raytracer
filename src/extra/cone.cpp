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

#include "cone.hpp"
#include "../Factory.hpp"

extern "C" void RegisterPlugin(Factory* f) {
    f->registerPrimitive("cones", [](dataPrimitive data, const std::string& name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<cone>(data, name);
    });
}
