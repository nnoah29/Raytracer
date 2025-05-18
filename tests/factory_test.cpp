#include <criterion/criterion.h>
#include "../src/Factory.hpp"
#include "../src/base/primitives/Sphere.hpp"
#include "../src/base/primitives/Plane.hpp"
#include "../src/base/lights/DirectionalLight.hpp"
#include "../src/base/lights/PointLight.hpp"

// Test de création de Factory
Test(Factory, creation)
{
    Factory factory;
    cr_assert(true, "La création de Factory devrait fonctionner");
}

// Test d'enregistrement et de création de primitives
Test(Factory, register_and_create_primitive)
{
    Factory factory;
    
    dataPrimitive sphereData;
    sphereData.name = "test_sphere";
    sphereData.position = Vecteur(0, 0, 0);
    sphereData.radius = 1.0;
    sphereData.material.color = Color(1, 0, 0);
    
    std::shared_ptr<IPrimitive> sphere = factory.Primitive("spheres", sphereData);
    
    cr_assert(sphere != nullptr, "La sphère ne devrait pas être null");
    
    std::shared_ptr<Sphere> sphereCast = std::dynamic_pointer_cast<Sphere>(sphere);
    cr_assert(sphereCast != nullptr, "L'objet devrait être une sphère");
}

// Test d'enregistrement et de création de plans
Test(Factory, register_and_create_plane)
{
    Factory factory;
    
    dataPrimitive planeData;
    planeData.name = "test_plane";
    planeData.position = Vecteur(0, 0, 0);
    planeData.normal = Vecteur(0, 1, 0);
    planeData.material.color = Color(0, 1, 0);
    
    std::shared_ptr<IPrimitive> plane = factory.Primitive("planes", planeData);
    
    cr_assert(plane != nullptr, "Le plan ne devrait pas être null");
    
    std::shared_ptr<Plane> planeCast = std::dynamic_pointer_cast<Plane>(plane);
    cr_assert(planeCast != nullptr, "L'objet devrait être un plan");
}

Test(Factory, register_and_create_directional_light)
{
    Factory factory;
    
    dataLight lightData;
    lightData.name = "test_directional";
    lightData.position = Vecteur(0, 0, 0);
    lightData.direction = Vecteur(1, 0, 0);
    
    std::shared_ptr<ILight> light = factory.Light("directional", lightData);
    
    cr_assert(light != nullptr, "La lumière ne devrait pas être null");
    
    std::shared_ptr<DirectionalLight> lightCast = std::dynamic_pointer_cast<DirectionalLight>(light);
    cr_assert(lightCast != nullptr, "L'objet devrait être une lumière directionnelle");
    
    Point dummy = {0, 0, 0};
    Vecteur dir = light->getDirectionFrom(dummy);
    cr_assert_eq(dir.x, 1, "direction.x devrait être 1");
    cr_assert_eq(dir.y, 0, "direction.y devrait être 0");
    cr_assert_eq(dir.z, 0, "direction.z devrait être 0");
}

// Test d'enregistrement et de création de lumières ponctuelles
Test(Factory, register_and_create_point_light)
{
    Factory factory;
    
    dataLight lightData;
    lightData.name = "test_point";
    lightData.position = Vecteur(0, 0, 10);
    lightData.direction = Vecteur(0, 0, 0);
    
    std::shared_ptr<ILight> light = factory.Light("point", lightData);
    
    cr_assert(light != nullptr, "La lumière ne devrait pas être null");
    
    std::shared_ptr<PointLight> lightCast = std::dynamic_pointer_cast<PointLight>(light);
    cr_assert(lightCast != nullptr, "L'objet devrait être une lumière ponctuelle");
    
    Point p = {0, 0, 0};
    Vecteur dir = light->getDirectionFrom(p);
    cr_assert_eq(dir.x, 0, "direction.x devrait être 0");
    cr_assert_eq(dir.y, 0, "direction.y devrait être 0");
    cr_assert_eq(dir.z, 10, "direction.z devrait être 10");
}

// Test d'erreur pour primitive inexistante
Test(Factory, primitive_not_found)
{
    Factory factory;
    
    dataPrimitive data;
    data.name = "test";
    
    bool exceptionThrown = false;
    try {
        factory.Primitive("nonexistent", data);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
        cr_assert_str_eq(e.what(), "Primitive 'nonexistent' does not exist", "Le message d'erreur devrait être correct");
    }
    
    cr_assert(exceptionThrown, "Une exception devrait être lancée pour une primitive inexistante");
}

// Test d'erreur pour lumière inexistante
Test(Factory, light_not_found)
{
    Factory factory;
    
    dataLight data;
    data.name = "test";
    
    bool exceptionThrown = false;
    try {
        factory.Light("nonexistent", data);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
        cr_assert_str_eq(e.what(), "Light 'nonexistent' does not exist", "Le message d'erreur devrait être correct");
    }
    
    cr_assert(exceptionThrown, "Une exception devrait être lancée pour une lumière inexistante");
}

// Test d'enregistrement personnalisé de primitive
Test(Factory, custom_primitive_registration)
{
    Factory factory;
    
    factory.registerPrimitive("custom", [](dataPrimitive data, const std::string& name) -> std::shared_ptr<IPrimitive> {
        return std::make_shared<Sphere>(data, name);
    });
    
    dataPrimitive customData;
    customData.name = "test_custom";
    customData.position = Vecteur(0, 0, 0);
    customData.radius = 2.0;
    customData.material.color = Color(0, 0, 1);
    
    std::shared_ptr<IPrimitive> custom = factory.Primitive("custom", customData);
    
    cr_assert(custom != nullptr, "La primitive personnalisée ne devrait pas être null");
}

// Test de désinscription de primitives
Test(Factory, unregister_primitives)
{
    Factory factory;
    
    factory.unregisterPrimitive();
    
    dataPrimitive data;
    data.name = "test";
    
    bool exceptionThrown = false;
    try {
        factory.Primitive("spheres", data);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
    }
    
    cr_assert(exceptionThrown, "Une exception devrait être lancée après désinscription des primitives");
}