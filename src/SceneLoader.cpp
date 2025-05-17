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

#include "SceneLoader.hpp"


SceneLoader::SceneLoader(const std::string& path, int ac)
{
    if (!std::filesystem::exists(path)) throw std::runtime_error("No Scene Found");
    try {
        cfg.readFile(path.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
    }
    //std::cout << "Scene Loading..." << std::endl;
    loadCamera(cfg.lookup("camera"));
    loadPrimitives(cfg.lookup("primitives"));
    loadLights(cfg.lookup("lights"));
    //std::cout << "Scene Loaded" << std::endl;
    (void)ac;
}

void SceneLoader::loadCamera(const libconfig::Setting& camera) const
{
    //std::cout << "Camera Loading..." << std::endl;
    if (camera.exists("resolution")) {
        const auto& res = camera["resolution"];
        if (res.exists("width")) c->resolution.width = res["width"];
        if (res.exists("height")) c->resolution.height = res["height"];
    }

    if (camera.exists("position")) {
        const auto& pos = camera["position"];
        if (pos.exists("x")) c->position.x = pos["x"];
        if (pos.exists("y")) c->position.y = pos["y"];
        if (pos.exists("z")) c->position.z = pos["z"];
    }

    if (camera.exists("rotation")) {
        const auto& rot = camera["rotation"];
        if (rot.exists("x")) c->rotation.x = rot["x"];
        if (rot.exists("y")) c->rotation.y = rot["y"];
        if (rot.exists("z")) c->rotation.z = rot["z"];
    }

    if (camera.exists("fieldOfView")) c->fov = camera["fieldOfView"];
    //std::cout << "Camera Loaded" << std::endl;
}

void applyTranslation(dataPrimitive& data)
{
    data = data;
}

void applyRotation(dataPrimitive& data)
{
    data = data;
}

void appyShear(dataPrimitive& data) {
    data = data;

}

void applyScale(dataPrimitive& data)
{
    data = data;
}

void applyMatrix(dataPrimitive& data)
{
    data = data;
}

void SceneLoader::loadPrimitives(const libconfig::Setting& primitives)
{
    //std::cout << "Primitives Loading..." << std::endl;
    for (int i = 0; i < primitives.getLength(); i++) {
        const libconfig::Setting& p = primitives[i];
        std::string name = p.getName();

        if (!p.isList()) {
            std::cerr << "Expected a list under " << name << std::endl;
            continue;
        }
        for (int j = 0; j < p.getLength(); j++) {
            const libconfig::Setting& item = p[j];
            dataPrimitive data;
            bool translation_is_define = false;
            bool rotation_is_define = false;
            bool scale_is_define = false;
            bool shear_is_define = false;
            // Nom
            data.name = name;

            // Position
            if (item.exists("x")) data.position.x = item["x"];
            if (item.exists("y")) data.position.y = item["y"];
            if (item.exists("z")) data.position.z = item["z"];

            // Couleur
            if (item.exists("color")) {
                const auto& c = item["color"];
                if (c.exists("r")) data.material.color.r = c["r"];
                if (c.exists("g")) data.material.color.g = c["g"];
                if (c.exists("b")) data.material.color.b = c["b"];
                data.material.color = data.material.color / 255.0;
            }

            // Propriétés géométriques
            if (item.exists("r")) data.radius = item["r"]; //rayon
            if (item.exists("h")) data.height = item["h"]; //hauteur
            if (item.exists("l")) data.length = item["l"]; //longueur
            if (item.exists("w")) data.width  = item["w"]; //largeur
            if (item.exists("corner")) data.corner = item["corner"]; //angle

            // Apparence
            if (item.exists("shininess")){    data.material.shininess = item["shininess"]; data.material.shininess_is_define = true; }
            if (item.exists("reflectivity")){ data.material.reflectivity = item["reflectivity"]; data.material.reflectivity_is_define = true; }
            if (item.exists("transparency")){ data.material.transparency = item["transparency"]; data.material.transparency_is_define = true; }

            // transformation
            if (item.exists("translation")) {
                const auto& t = item["translation"];
                translation_is_define = true;
                data.transform.translation.x = t["x"];
                data.transform.translation.y = t["y"];
                data.transform.translation.z = t["z"];
                if (t.exists("at")) {
                    const std::string at = t["at"];
                    data.transform.at_t = at;
                }
            }
            if (item.exists("rotation")) {
                const auto& r = item["rotation"];
                rotation_is_define = true;
                data.transform.rotation.x = r["x"];
                data.transform.rotation.y = r["y"];
                data.transform.rotation.z = r["z"];
                if (r.exists("at")) {
                    const std::string at = r["at"];
                    data.transform.at_r = at;
                }
            }
            if (item.exists("scale")) {
                const auto& s = item["scale"];
                scale_is_define = true;
                data.transform.scale.x = s["x"];
                data.transform.scale.y = s["y"];
                data.transform.scale.z = s["z"];
                if (s.exists("at")) {
                    const std::string at = s["at"];
                    data.transform.at_sc = at;
                }
            }
            if (item.exists("shear")) {
                const auto& s = item["shear"];
                shear_is_define = true;
                data.transform.shear.x = s["x"];
                data.transform.shear.y = s["y"];
                data.transform.shear.z = s["z"];
                if (s.exists("at")) {
                    const std::string at = s["at"];
                    data.transform.at_sh = at;
                }
            }

            // formes planes
            if (item.exists("axis")) {
                std::string axis = item["axis"];
                if (axis == "X" || axis == "x") {
                    data.normal = {1, 0, 0};
                } else if (axis == "Y" || axis == "y") {
                    data.normal = {0, 1, 0};
                } else if (axis == "Z" || axis == "z") {
                    data.normal = {0, 0, 1};
                }
            }
            if (item.exists("axis") && item.exists("position")) {
                std::string axis = item["axis"];
                float pos = item["position"];
                if (axis == "X" || axis == "x") {
                    data.reference = {pos, 0, 0};
                } else if (axis == "Y" || axis == "y") {
                    data.reference = {0, pos, 0};
                } else if (axis == "Z" || axis == "z") {
                    data.reference = {0, 0, pos};
                }
            }

            if (translation_is_define) applyTranslation(data);
            if (rotation_is_define) applyRotation(data);
            if (scale_is_define) applyScale(data);
            if (shear_is_define) appyShear(data);


            ps.push_back(std::make_shared<dataPrimitive>(data));
        }
    }
    //std::cout << "Primitives Loaded" << std::endl;
}

void SceneLoader::loadLights(const libconfig::Setting& light)
{
    //std::cout << "Lights Loading..." << std::endl;
    if (light.exists("ambient"))
        ambient_intensity = light["ambient"];
    if (light.exists("diffuse"))
        diffuse_intensity = light["diffuse"];

    if (light.exists("point")) {
        const auto& points = light["point"];
        for (int i = 0; i < points.getLength(); i++) {
            const auto& pt = points[i];
            dataLight l;
            l.name = "point";
            l.position = {
                pt["x"], pt["y"], pt["z"]
            };
            if (pt.exists("color")) {
                const auto& c = pt["color"];
                if (c.exists("r")) l.intensity.r = c["r"];
                if (c.exists("g")) l.intensity.g = c["g"];
                if (c.exists("b")) l.intensity.b = c["b"];

            }
            ls.push_back(std::make_shared<dataLight>(l));
        }
    }
    if (light.exists("directional")) {
        const auto& dirs = light["directional"];
        for (int i = 0; i < dirs.getLength(); i++) {
            const auto& dir = dirs[i];
            dataLight l;
            l.name = "directional";
            l.direction = {
                dir["x"], dir["y"], dir["z"]
            };
            if (dir.exists("color")) {
                const auto& c = dir["color"];
                if (c.exists("r")) l.intensity.r = c["r"];
                if (c.exists("g")) l.intensity.g = c["g"];
                if (c.exists("b")) l.intensity.b = c["b"];
                l.intensity = l.intensity / 255.0;
            }
            ls.push_back(std::make_shared<dataLight>(l));
        }
    }
    //std::cout << "Lights Loaded" << std::endl;
}

Scene SceneLoader::createScene(Factory& f) const {
    Scene s(c, ps, ls, f);
    s.ambient_intensity = ambient_intensity;
    s.diffuse_intensity = diffuse_intensity;
    return s;
}