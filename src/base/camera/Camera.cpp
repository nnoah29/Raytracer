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
#include "../../../includes/my.hpp"

#include <iostream>
#include <random>

Vecteur Camera::getPosition() const{
    return position;
}

Vecteur Camera::getRotation() const{
    return rotation;
}

Resolution Camera::getResolution() const{
    return resolution;
}
float Camera::getFOV() const{
    return fov;
}

void Camera::setResolution(int width, int height){
    resolution.width = width;
    resolution.height = height;
}

void Camera::setPosition(const Vecteur& position){
    this->position = position;
}

void Camera::setRotation(const Vecteur& rotation){
    this->rotation = rotation;
}

void Camera::setFOV(float fov){
    this->fov = fov;
}

Viewport::Viewport(float fov, float aspect_ratio, const local3D& l, Resolution r)
{
    const float theta = degreesToRadians(fov);
    const float h = std::tan(theta / 2.0f);
    height = 2.0f * h;
    width  = aspect_ratio * height;

    horizontal =  l.u * width;
    vertical   = -l.v * height;

    D_u = horizontal / static_cast<float>(r.width);
    D_v = vertical   / static_cast<float>(r.height);

    const auto upper_left_corner = l.origin - (l.w) - (horizontal * 0.5f) - (vertical * 0.5f);
    pixel_00 = upper_left_corner + (D_u + D_v) * 0.5f;
}

Camera::Camera(float fov, Resolution resolution, Point position, Vecteur rotation) {
    this->fov = fov;
    this->resolution = resolution;
    this->position = position;
    this->rotation = rotation;

    lookFrom = position;
    lookAt = lookFrom;
    lookAt.z = -1.0f;
    imageWidth = resolution.width;
    imageHeight = resolution.height;

    w = (lookFrom - lookAt).normalized();
    u = (cross(up, w)).normalized();
    v = (cross(w, u)).normalized();

    l = local3D(position, u, v, w);
    viewport = Viewport(fov, aspectRatio, l, resolution);
};

Vecteur Camera::applyRotation(const Vecteur &dir, const Vecteur &rotation) {
    // Conversion en radians
    const float pitch = rotation.x * M_PI / 180.0f; // rotation autour de X
    const float yaw   = rotation.y * M_PI / 180.0f; // rotation autour de Y
    const float roll  = rotation.z * M_PI / 180.0f; // rotation autour de Z

    // Pré-calcul des cosinus/sinus
    const float cosPitch = std::cos(pitch);
    const float sinPitch = std::sin(pitch);
    const float cosYaw   = std::cos(yaw);
    const float sinYaw   = std::sin(yaw);
    const float cosRoll  = std::cos(roll);
    const float sinRoll  = std::sin(roll);

    // Matrice de rotation complète (Z * X * Y) appliquée au vecteur dir
    Vecteur rotated;
    rotated.x =
        dir.x * (cosYaw * cosRoll + sinYaw * sinPitch * sinRoll) +
        dir.y * (cosPitch * sinRoll) +
        dir.z * (sinYaw * cosRoll - cosYaw * sinPitch * sinRoll);

    rotated.y =
        dir.x * (-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll) +
        dir.y * (cosPitch * cosRoll) +
        dir.z * (-sinYaw * sinRoll - cosYaw * sinPitch * cosRoll);

    rotated.z =
        dir.x * (sinYaw * cosPitch) +
        dir.y * (-sinPitch) +
        dir.z * (cosYaw * cosPitch);

    return rotated.normalized();
}

double Camera::random_double() {
    return std::rand() / (RAND_MAX + 1.0);
}

Vecteur Camera::sample_square() {
    return {static_cast<float>(random_double() - 0.5), static_cast<float>(random_double() - 0.5), 0};
}

Vecteur sample_square_seed(int i, int j)
{
    std::mt19937 rng (i * 48487884548 ^ j * 885484848848);
    std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
    return {dist(rng), dist(rng), 0};
}

Ray Camera::generateRay(int i, int j) const
{
    Vecteur offset{0, 0, 0};
    if (antialiasing)
        offset = sample_square();
    const Vecteur pixel = viewport.pixel_00 + (viewport.D_u * (i + offset.x)) + (viewport.D_v * (j + offset.y));

    const auto origin = position;
    auto direction = pixel - origin;
    direction = applyRotation(direction, rotation);
    return {origin, direction};
}
