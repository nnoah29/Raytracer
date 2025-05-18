#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include "../src/base/camera/Camera.hpp"
#include <cmath>

// Test de création de caméra
Test(Camera, creation)
{
    Resolution res = {800, 600};
    Point pos = {0, 0, 0};
    Vecteur rot = {0, 0, 0};
    float fov = 90.0f;

    Camera camera(fov, res, pos, rot);

    cr_assert_eq(camera.getResolution().width, 800, "La résolution en largeur devrait être 800");
    cr_assert_eq(camera.getResolution().height, 600, "La résolution en hauteur devrait être 600");
    cr_assert_eq(camera.getPosition().x, 0, "La position x devrait être 0");
    cr_assert_eq(camera.getPosition().y, 0, "La position y devrait être 0");
    cr_assert_eq(camera.getPosition().z, 0, "La position z devrait être 0");
    cr_assert_eq(camera.getRotation().x, 0, "La rotation x devrait être 0");
    cr_assert_eq(camera.getRotation().y, 0, "La rotation y devrait être 0");
    cr_assert_eq(camera.getRotation().z, 0, "La rotation z devrait être 0");
    cr_assert_float_eq(camera.getFOV(), 90.0f, 0.001f, "Le FOV devrait être 90.0");
}

// Test des setters
Test(Camera, setters)
{
    Resolution res = {800, 600};
    Point pos = {0, 0, 0};
    Vecteur rot = {0, 0, 0};
    float fov = 90.0f;

    Camera camera(fov, res, pos, rot);

    camera.setPosition({1, 2, 3});
    cr_assert_eq(camera.getPosition().x, 1, "La position x devrait être 1");
    cr_assert_eq(camera.getPosition().y, 2, "La position y devrait être 2");
    cr_assert_eq(camera.getPosition().z, 3, "La position z devrait être 3");

    camera.setRotation({10, 20, 30});
    cr_assert_eq(camera.getRotation().x, 10, "La rotation x devrait être 10");
    cr_assert_eq(camera.getRotation().y, 20, "La rotation y devrait être 20");
    cr_assert_eq(camera.getRotation().z, 30, "La rotation z devrait être 30");

    camera.setResolution(1920, 1080);
    cr_assert_eq(camera.getResolution().width, 1920, "La résolution en largeur devrait être 1920");
    cr_assert_eq(camera.getResolution().height, 1080, "La résolution en hauteur devrait être 1080");

    camera.setFOV(60.0f);
    cr_assert_float_eq(camera.getFOV(), 60.0f, 0.001f, "Le FOV devrait être 60.0");
}

// Test de la génération de rayon
Test(Camera, ray_generation)
{
    Resolution res = {800, 600};
    Point pos = {0, 0, 0};
    Vecteur rot = {0, 0, 0};
    float fov = 90.0f;

    Camera camera(fov, res, pos, rot);

    Ray ray = camera.generateRay(res.width / 2, res.height / 2);

    cr_assert_eq(ray.origin().x, 0, "L'origine x du rayon devrait être 0");
    cr_assert_eq(ray.origin().y, 0, "L'origine y du rayon devrait être 0");
    cr_assert_eq(ray.origin().z, 0, "L'origine z du rayon devrait être 0");
    cr_assert_float_eq(ray.direction().z, -1.0f, 0.1f, "La direction z du rayon devrait être proche de -1.0");
}

// Test de la rotation de la caméra
Test(Camera, rotation_effect)
{
    Resolution res = {800, 600};
    Point pos = {0, 0, 0};
    float fov = 90.0f;

    Vecteur rot = {0, 90, 0};
    Camera camera(fov, res, pos, rot);
    Ray ray = camera.generateRay(res.width / 2, res.height / 2);

    cr_assert_float_eq(ray.direction().x, -1.0f, 0.1f, "La direction x du rayon devrait être proche de -1.0");
    cr_assert_float_eq(ray.direction().z, 0.0f, 0.1f, "La direction z du rayon devrait être proche de 0.0");
}

// Test avec différentes positions de caméra
Test(Camera, different_positions)
{
    Resolution res = {800, 600};
    Vecteur rot = {0, 0, 0};
    float fov = 90.0f;

    Point pos = {10, 5, 3};
    Camera camera(fov, res, pos, rot);
    Ray ray = camera.generateRay(res.width / 2, res.height / 2);

    cr_assert_eq(ray.origin().x, 10, "L'origine x du rayon devrait être 10");
    cr_assert_eq(ray.origin().y, 5, "L'origine y du rayon devrait être 5");
    cr_assert_eq(ray.origin().z, 3, "L'origine z du rayon devrait être 3");
}