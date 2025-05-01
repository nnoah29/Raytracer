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

#ifndef APRIMITIVE_HPP
#define APRIMITIVE_HPP
#include <string>

#include "IPrimitive.hpp"
#include "my.hpp"


class APrimitive : public IPrimitive {
protected:
    std::string name;
public:
    APrimitive(const dataPrimitive& data, const std::string& name) {
        (void)data;
        (void)name;
    };

    ~APrimitive() override = default;
    bool hit(const Ray& ray, float t_min, float t_max, PointOfImpact p) const override = 0;
};



#endif //APRIMITIVE_HPP
