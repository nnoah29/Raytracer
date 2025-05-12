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
        cfg.readFile(path);
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
    }
    std::cout << "Scene Loading..." << std::endl;
    loadCamera(cfg.lookup("camera"));
    loadPrimitives(cfg.lookup("primitives"));
    loadLights(cfg.lookup("lights"));
    std::cout << "Scene Loaded" << std::endl;
    (void)ac;
}

void SceneLoader::loadCamera(const libconfig::Setting& camera) const
{
    std::cout << "Camera Loading..." << std::endl;
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
    std::cout << "Camera Loaded" << std::endl;
}

void SceneLoader::loadPrimitives(const libconfig::Setting& primitives)
{
    std::cout << "Primitives Loading..." << std::endl;
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
            // Nom
            data.name = name;

            // Position
            if (item.exists("x")) data.position.x = item["x"];
            if (item.exists("y")) data.position.y = item["y"];
            if (item.exists("z")) data.position.z = item["z"];

            // Couleur
            if (item.exists("color")) {
                const auto& c = item["color"];
                if (c.exists("r")) data.color.r = c["r"];
                if (c.exists("g")) data.color.g = c["g"];
                if (c.exists("b")) data.color.b = c["b"];
            }

            // Propriétés géométriques
            if (item.exists("r")) data.radius = item["r"]; //rayon
            if (item.exists("h")) data.height = item["h"]; //hauteur
            if (item.exists("l")) data.length = item["l"]; //longueur
            if (item.exists("w")) data.width  = item["w"]; //largeur

            // Apparence
            if (item.exists("shininess"))    data.shininess = item["shininess"];
            if (item.exists("reflectivity")) data.reflectivity = item["reflectivity"];
            if (item.exists("transparency")) data.transparency = item["transparency"];

            // transformation
            if (item.exists("translation")) {
                data.transform.translation.x = item["translation"]["x"];
                data.transform.translation.y = item["translation"]["y"];
                data.transform.translation.z = item["translation"]["z"];
            }
            if (item.exists("rotation")) {
                data.transform.rotation.x = item["rotation"]["x"];
                data.transform.rotation.y = item["rotation"]["y"];
                data.transform.rotation.z = item["rotation"]["z"];
            }
            if (item.exists("scale")) {
                data.transform.scale.x = item["scale"]["x"];
                data.transform.scale.y = item["scale"]["y"];
                data.transform.scale.z = item["scale"]["z"];
            }
            if (item.exists("shear")) {
                data.transform.shear.x = item["shear"]["x"];
                data.transform.shear.y = item["shear"]["y"];
                data.transform.shear.z = item["shear"]["z"];
            }
            // formes planes
            if (item.exists("axis") && item.exists("position")) {
                std::string axis = item["axis"];
                float pos = item["position"];

                if (axis == "X" || axis == "x") {
                    data.normal = {1, 0, 0};
                    data.reference = {pos, 0, 0};
                } else if (axis == "Y" || axis == "y") {
                    data.normal = {0, 1, 0};
                    data.reference = {0, pos, 0};
                } else if (axis == "Z" || axis == "z") {
                    data.normal = {0, 0, 1};
                    data.reference = {0, 0, pos};
                }
            }
            ps.push_back(std::make_shared<dataPrimitive>(data));
        }
    }
    std::cout << "Primitives Loaded" << std::endl;
}

void SceneLoader::loadLights(const libconfig::Setting& light)
{
    std::cout << "Lights Loading..." << std::endl;
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
            ls.push_back(std::make_shared<dataLight>(l));
        }
    }
    std::cout << "Lights Loaded" << std::endl;
}

Scene SceneLoader::createScene(Factory& f) const {
    return {c, ps, ls, f};
}