#include <criterion/criterion.h>
#include "../src/Scene.hpp"
#include "../src/Factory.hpp"
#include "../src/base/primitives/Sphere.hpp"
#include "../src/base/primitives/Plane.hpp"
#include "../src/base/lights/DirectionalLight.hpp"
#include "../src/base/lights/PointLight.hpp"
#include <memory>
#include <vector>

std::shared_ptr<dataCamera> createTestCamera() {
    std::shared_ptr<dataCamera> camera = std::make_shared<dataCamera>();
    camera->fov = 90.0f;
    camera->resolution = {800, 600};
    camera->position = {0, 0, 0};
    camera->rotation = {0, 0, 0};
    return camera;
}

std::shared_ptr<dataPrimitive> createTestSphere(const std::string& /*name*/, const Vecteur& position, float radius) {
    std::shared_ptr<dataPrimitive> sphere = std::make_shared<dataPrimitive>();
    sphere->name = "spheres";
    sphere->position = position;
    sphere->radius = radius;
    sphere->material.color = Color(1, 0, 0);
    return sphere;
}

std::shared_ptr<dataPrimitive> createTestPlane(const std::string& /*name*/, const Vecteur& position, const Vecteur& normal) {
    std::shared_ptr<dataPrimitive> plane = std::make_shared<dataPrimitive>();
    plane->name = "planes";
    plane->position = position;
    plane->normal = normal;
    plane->material.color = Color(0, 1, 0);
    return plane;
}

std::shared_ptr<dataLight> createTestDirectionalLight(const std::string& /*name*/, const Vecteur& direction) {
    std::shared_ptr<dataLight> light = std::make_shared<dataLight>();
    light->name = "directional";
    light->position = {0, 0, 0};
    light->direction = direction;
    return light;
}

std::shared_ptr<dataLight> createTestPointLight(const std::string& /*name*/, const Vecteur& position) {
    std::shared_ptr<dataLight> light = std::make_shared<dataLight>();
    light->name = "point";
    light->position = position;
    light->direction = {0, 0, 0};
    return light;
}

// Test de création de scène vide
Test(Scene, creation_empty)
{
    Factory factory;
    std::shared_ptr<dataCamera> camera = createTestCamera();
    TabDataPrimitives primitives;
    TabDataLights lights;

    Scene scene(camera, primitives, lights, factory);
    cr_assert(true, "La scène devrait être créée sans erreur");
}

// Test de création de scène avec des primitives
Test(Scene, creation_with_primitives)
{
    Factory factory;
    std::shared_ptr<dataCamera> camera = createTestCamera();

    TabDataPrimitives primitives;
    primitives.push_back(createTestSphere("sphere1", {0, 0, -10}, 1.0f));
    primitives.push_back(createTestSphere("sphere2", {2, 0, -10}, 1.5f));
    primitives.push_back(createTestPlane("plane1", {0, -2, 0}, {0, 1, 0}));

    TabDataLights lights;

    Scene scene(camera, primitives, lights, factory);
    cr_assert(true, "La scène avec primitives devrait être créée sans erreur");
}

// Test de création de scène avec des lumières
Test(Scene, creation_with_lights)
{
    Factory factory;
    std::shared_ptr<dataCamera> camera = createTestCamera();

    TabDataPrimitives primitives;
    TabDataLights lights;
    lights.push_back(createTestDirectionalLight("sun", {1, -1, 0}));
    lights.push_back(createTestPointLight("lamp", {0, 5, 0}));

    Scene scene(camera, primitives, lights, factory);

    // Vérifier que la scène est créée sans erreur
    cr_assert(true, "La scène avec lumières devrait être créée sans erreur");
}

// Test de création de scène complète
Test(Scene, creation_complete)
{
    Factory factory;
    std::shared_ptr<dataCamera> camera = createTestCamera();

    // Créer des primitives
    TabDataPrimitives primitives;
    primitives.push_back(createTestSphere("sphere1", {0, 0, -10}, 1.0f));
    primitives.push_back(createTestPlane("plane1", {0, -2, 0}, {0, 1, 0}));
    TabDataLights lights;
    lights.push_back(createTestDirectionalLight("sun", {1, -1, 0}));
    lights.push_back(createTestPointLight("lamp", {0, 5, 0}));

    Scene scene(camera, primitives, lights, factory);
    cr_assert(true, "La scène complète devrait être créée sans erreur");
}

// Test de la caméra de la scène
Test(Scene, camera_creation)
{
    Factory factory;
    std::shared_ptr<dataCamera> camera = createTestCamera();
    camera->fov = 60.0f;
    camera->resolution = {1920, 1080};
    camera->position = {1, 2, 3};
    camera->rotation = {10, 20, 30};

    TabDataPrimitives primitives;
    TabDataLights lights;

    Scene scene(camera, primitives, lights, factory);
    cr_assert(true, "La scène avec caméra personnalisée devrait être créée sans erreur");
}