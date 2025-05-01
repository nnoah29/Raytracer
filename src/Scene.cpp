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

Scene::Scene(const std::shared_ptr<dataCamera>& c, const TabDataPrimitives& ps, const TabDataLights& ls)
: camera(c->fov, c->resolution, c->position, c->rotation)
{
    loadObjects(ps);
    loadLights(ls);
}

void Scene::loadObjects(const TabDataPrimitives& ps)
{
    (void)ps;
}

void Scene::loadLights(const TabDataLights& ls)
{
    (void)ls;
}
