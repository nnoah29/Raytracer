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

#include "Scene.hpp"
#include <iostream>
#include "base/primitives/Sphere.hpp"

Scene::Scene(const std::shared_ptr<dataCamera>& c, const TabDataPrimitives& ps, const TabDataLights& ls, const Factory& f)
: factory(f), camera(c->fov, c->resolution, c->position, c->rotation)
{
    loadObjects(ps);
    loadLights(ls);
}

void Scene::loadObjects(const TabDataPrimitives& ps)
{
    for (const auto& primitiveData : ps) {
        std::shared_ptr<IPrimitive> obj;

        obj = factory.Primitive(primitiveData->name, *primitiveData);
        objs.push_back(obj);
        std::cout << "Primitive " << primitiveData->name << " is added" << std::endl;
    }
}

void Scene::loadLights(const TabDataLights& ls)
{
    for (const auto& lightData : ls) {
        std::shared_ptr<ILight> light;

        light = factory.Light(lightData->name, *lightData);
        lights.push_back(light);
        std::cout << "Light " << lightData->name << " is added" << std::endl;
    }
}
