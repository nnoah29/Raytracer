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

typedef struct local3D
{
    Point origin;
    Vecteur u, v, w;

    local3D(Point origin, Vecteur u, Vecteur v, Vecteur w) : origin(origin), u(u), v(v), w(w) {};
    local3D() = default;
} local3D;

typedef struct Viewport
{
    float height{};
    float width{};
    Vecteur horizontal;
    Vecteur vertical;
    Vecteur D_u;
    Vecteur D_v;
    Point pixel_00;

    Viewport() = default;
    Viewport(float fov, float aspect_ratio, const local3D& l, Resolution r);
} Viewport;

class Camera final : public ICamera {
protected:
    Resolution resolution{};
    Point position; //center
    Vecteur rotation;
    float fov = 0;

    Point lookFrom;
    Point lookAt;
    Vecteur up = Vecteur(0, 1, 0);
    int imageWidth, imageHeight;
    Vecteur u, v, w;
    local3D l;


public:
    float aspectRatio = 1920.0f / 1080.0f;
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
    static Vecteur sample_square();
    Ray generateRay(int i, int j) const;

    Camera(float fov, Resolution resolution, Point position, Vecteur rotation);
    static Vecteur applyRotation(const Vecteur& dir, const Vecteur& rotation);
    static double random_double();
};



#endif //CAMERA_HPP
