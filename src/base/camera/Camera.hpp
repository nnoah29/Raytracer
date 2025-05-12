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

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <ostream>

#include "conf.hpp"
#include "../../interfaces/ICamera.hpp"
#include "my.hpp"

typedef struct Viewport
{
    float height;
    float width;
    Vecteur horizontal;
    Vecteur vertical;
    Point lower_left_corner;

    Viewport(float fov, float aspect_ratio, Vecteur position)
    {
        height = static_cast<float>(std::tan((fov * 0.5f) * M_PI / 180.0f)) * 2.0f;
        width  = aspect_ratio * height;
        horizontal = Vecteur(width,  0.0f, 0.0f);
        vertical   = Vecteur(0.0f, -height, 0.0f);

        lower_left_corner = position - horizontal*0.5f - vertical*0.5f - Vecteur(0,0,1);
    }

} Viewport;

class Camera final : public ICamera {
protected:
    Resolution resolution;
    Point position;
    Vecteur rotation;
    float fov = 0;

public:
    float aspectRatio = ASPECT_RATIO;
    int max_depth = LIGHT_DEPTH;
    Viewport viewport;

    Point getPosition() const override;
    Vecteur getRotation() const override;
    Resolution getResolution() const override;
    float getFOV() const override;

    void setResolution(int width, int height) override;
    void setPosition(const Vecteur& position) override;
    void setRotation(const Vecteur& rotation) override;
    void setFOV(float fov) override;
    Ray generateRay(int i, int j) const;

    Camera(float fov, Resolution resolution, Point position, Vecteur rotation);
    Camera(const Camera& camera) = delete;

};



#endif //CAMERA_HPP
