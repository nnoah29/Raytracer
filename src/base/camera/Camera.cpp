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

#include <iostream>

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

Vecteur applyRotation(const Vecteur &dir, const Vecteur &rotation) {
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

double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}
Vecteur sample_square() {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vecteur(random_double() - 0.5, random_double() - 0.5, 0);
}

Ray Camera::generateRay(int i, int j) const
{
    const auto offset = sample_square();
    const auto pixel = viewport.pixel_00
               + (viewport.D_u * (i + offset.x))
               + (viewport.D_v * (j + offset.y));

    const auto origin = position;
    auto direction = pixel - origin;


    if (i == resolution.width / 2 && j == resolution.height / 2) {
        std::cout << "Ray direction: " << direction.x << ", "
                  << direction.y << ", " << direction.z << std::endl;
    }
    if ((i == 0 && j == 0) || (i == resolution.width - 1 && j == resolution.height - 1)) {
        std::cout << "Corner ray dir: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
    }
    // std::cout << "Camera pos: " << position << "\n";
    // std::cout << "Ray dir center: " << direction.x << ", " << direction.y << ", " << direction.z << "\n";
    direction = applyRotation(direction, rotation);
    return {origin, direction};


    return Ray{position, direction};
}
