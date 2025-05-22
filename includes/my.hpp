/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 24/04/25.                                          
**         |___/ 
*/

#ifndef MY_HPP
#define MY_HPP
#include "Vecteur.hpp"
#include <cmath>
#include <string>
#include <map>
#include "Vecteur.hpp"
#include "Color.hpp"
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

extern bool antialiasing;

typedef struct Resolution {
    int width;
    int height;
} Resolution;

typedef struct Transform {
    Vecteur translation = {0.0f, 0.0f, 0.0f};
    Vecteur rotation    = {0.0f, 0.0f, 0.0f};
    Vecteur scale       = {1.0f, 1.0f, 1.0f};
    Vecteur shear       = {0.0f, 0.0f, 0.0f};
    std::array<std::array<float, 3>, 3> matrix {};
    std::string at_t;
    std::string at_r;
    std::string at_m;
    std::string at_sc;
    std::string at_sh;

    Vecteur applyTranslation(const Vecteur& pt) const {
        return pt + translation;
    }

    Vecteur applyRotation(Vecteur& pt) const {
        // Rotation autour de X
        const float cosx = std::cos(rotation.x);
        const float sinx = std::sin(rotation.x);
        pt = {
            pt.x * 1,
            pt.y * cosx - pt.z * sinx,
            pt.y * sinx + pt.z * cosx
        };
        // Rotation autour de Y
        const float cosy = std::cos(rotation.y);
        const float siny = std::sin(rotation.y);
        pt = {
            pt.x * cosy + pt.z * siny,
            pt.y * 1,
            -pt.x * siny + pt.z * cosy
        };
        // Rotation autour de Z
        const float cosz = std::cos(rotation.z);
        const float sinz = std::sin(rotation.z);
        pt = {
            pt.x * cosz - pt.y * sinz,
            pt.x * sinz + pt.y * cosz,
            pt.z * 1
        };
        return pt;
    }

    Vecteur appyShear(const Vecteur& pt) const {
        return {
            pt.x + shear.x * pt.y + shear.y * pt.z,
            pt.y + shear.z * pt.z,
            pt.z
        };
    }

    Vecteur applyScale(const Vecteur& pt) const
    {
        return {
        pt.x * scale.x,
        pt.y * scale.y,
        pt.z * scale.z
        };
    }

    Vecteur applyMatrix(const Vecteur& p) const {
        const float x = p.x;
        const float y = p.y;
        const float z = p.z;

        float xp =
            matrix[0][0] * x +
            matrix[0][1] * y +
            matrix[0][2] * z;
        float yp =
            matrix[1][0] * x +
            matrix[1][1] * y +
            matrix[1][2] * z;
        float zp =
            matrix[2][0] * x +
            matrix[2][1] * y +
            matrix[2][2] * z;

        return {xp, yp, zp};
    }

} Transform;

typedef struct Material
{
    Color color = {1.0f, 1.0f, 1.0f};
    float shininess = 0.0f;
    float reflectivity = 0.0f;
    float transparency = 0.0f;

    bool shininess_is_define = false;
    bool reflectivity_is_define = false;
    bool transparency_is_define = false;
} Material;

typedef struct dataPrimitive {
    std::string name;

    // Transformation
    Vecteur position = {0.0f, 0.0f, 0.0f};
    Transform transform;

    // Apparence
    Material material;

    // Propriétés géométriques de base
    float radius   = 1.0f;
    float height   = 0.0f;
    float width    = 1.0f;
    float length   = 1.0f;
    float corner   = 1.0f;

    // Spécifique aux formes planes ou implicites
    Vecteur normal      = {0.0f, 1.0f, 0.0f};
    Point   reference   = {0.0f, 0.0f, 0.0f};

    // Propriétés génériques supplémentaires
    std::map<std::string, float> float_params;
    std::map<std::string, std::string> string_params;

} dataPrimitive;

typedef struct dataCamera {
    // Propriétés géométriques de base
    float fov{};
    Resolution resolution{0, 0};
    Point position{};
    Vecteur rotation{};

    // Propriétés génériques supplémentaires
    std::map<std::string, float> float_params;
    std::map<std::string, std::string> string_params;
} dataCamera;

typedef struct dataLight
{
    std::string name;
    Vecteur position;
    Vecteur direction;
    Color intensity{0.01f, 0.01f, 0.01f};

} dataLight;

using TabDataPrimitives = std::vector<std::shared_ptr<dataPrimitive>>;
using TabDataLights = std::vector<std::shared_ptr<dataLight>>;

float dot(const Vecteur& v1, const Vecteur& v2);
bool surrounds(float min, float x, float max);
Vecteur operator/(const Vecteur& v1, float t);
float degreesToRadians(float degrees);
Vecteur cross(const Vecteur& v1, const Vecteur& v2);


#endif //MY_HPP
