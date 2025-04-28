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

#include "Camera.hpp"

Vecteur Camera::getPosition() const override {
    return position;
}

Vecteur Camera::getRotation() const override {
    return rotation;
}

Resolution Camera::getResolution() const override {
    return resolution;
}
float Camera::getFOV() const override {
    return fov;
}

void Camera::setResolution(int width, int height) override {
    resolution.width = width;
    resolution.height = height;
}

void Camera::setPosition(const Vecteur& position) override {
    this->position = position;
}

void Camera::setRotation(const Vecteur& rotation) override {
    this->rotation = rotation;
}

void Camera::setFOV(float fov) override {
    this->fov = fov;
}

void Camera::initCamera()
{

}

Ray Camera::generateRay(auto i, auto j) const
{
    const float u = (i + 0.5f) / resolution.width;
    const float v = 1.0f - (j + 0.5f) / resolution.height;
    const Point cible = viewport.lower_left_corner + (viewport.horizontal * u) + (viewport.vertical * v);
    const Vecteur direction = (cible - position).normalized();

    return {position, direction};
}
