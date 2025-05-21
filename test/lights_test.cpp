#include <criterion/criterion.h>
#include "../src/base/lights/DirectionalLight.hpp"
#include "../src/base/lights/PointLight.hpp"

Test(Simple, basic_test)
{
    int a = 1;
    int b = 1;
    cr_assert_eq(a, b, "Les valeurs devraient être égales");
}

Test(Simple, string_test)
{
    std::string s1 = "test";
    std::string s2 = "test";
    cr_assert_str_eq(s1.c_str(), s2.c_str(), "Les chaînes devraient être égales");
}

// Test qui utilise uniquement la structure dataLight
Test(DataLight, basic_structure)
{
    dataLight d;
    d.name = "test_light";
    d.position = Vecteur(1, 2, 3);
    d.direction = Vecteur(4, 5, 6);

    cr_assert_str_eq(d.name.c_str(), "test_light", "Le nom devrait être 'test_light'");
    cr_assert_eq(d.position.x, 1, "position.x devrait être 1");
    cr_assert_eq(d.position.y, 2, "position.y devrait être 2");
    cr_assert_eq(d.position.z, 3, "position.z devrait être 3");
    cr_assert_eq(d.direction.x, 4, "direction.x devrait être 4");
    cr_assert_eq(d.direction.y, 5, "direction.y devrait être 5");
    cr_assert_eq(d.direction.z, 6, "direction.z devrait être 6");
}

Test(LightCreation, directional_light)
{
    dataLight d;
    d.name = "test_directional";
    d.position = Vecteur(0, 0, 0);
    d.direction = Vecteur(1, 0, 0);

    DirectionalLight light(d, "test_directional");

    cr_assert(true, "Si ce test passe, la création de DirectionalLight fonctionne");
}

// Test qui utilise la méthode getDirectionFrom
Test(LightMethod, get_direction)
{
    dataLight d;
    d.name = "test_directional";
    d.position = Vecteur(0, 0, 0);
    d.direction = Vecteur(1, 0, 0);

    DirectionalLight light(d, "test_directional");

    Point dummy = {0, 0, 0};
    Vecteur dir = light.getDirectionFrom(dummy);

    cr_assert_eq(dir.x, 1, "direction.x devrait être 1");
    cr_assert_eq(dir.y, 0, "direction.y devrait être 0");
    cr_assert_eq(dir.z, 0, "direction.z devrait être 0");
}

// Test qui utilise la méthode getIntensityAt
Test(LightMethod, get_intensity)
{
    dataLight d;
    d.name = "test_directional";
    d.position = Vecteur(0, 0, 0);
    d.direction = Vecteur(0, 0, -1);

    DirectionalLight light(d, "test_directional");

    PointOfImpact poi;
    poi.p = {0, 0, 0};
    poi.normal = {0, 0, -1};
    poi.material.color = Color(1, 0, 0); // rouge

    Color result = light.getIntensityAt(poi);

    cr_assert_float_eq(result.r, 1.0f, 0.001, "result.r devrait être 1.0");
    cr_assert_float_eq(result.g, 0.0f, 0.001, "result.g devrait être 0.0");
    cr_assert_float_eq(result.b, 0.0f, 0.001, "result.b devrait être 0.0");
}

Test(PointLightCreation, point_light)
{
    dataLight d;
    d.name = "test_point";
    d.position = Vecteur(0, 0, 10);
    d.direction = Vecteur(0, 0, 0);

    PointLight light(d, "test_point");

    cr_assert(true, "Si ce test passe, la création de PointLight fonctionne");
}

Test(PointLightMethod, get_direction)
{
    dataLight d;
    d.name = "test_point";
    d.position = Vecteur(0, 0, 10);
    d.direction = Vecteur(0, 0, 0);

    PointLight light(d, "test_point");

    Point p = {0, 0, 0};
    Vecteur dir = light.getDirectionFrom(p);

    cr_assert_eq(dir.x, 0, "direction.x devrait être 0");
    cr_assert_eq(dir.y, 0, "direction.y devrait être 0");
    cr_assert_eq(dir.z, 10, "direction.z devrait être 10");
}

Test(PointLightMethod, get_intensity)
{
    dataLight d;
    d.name = "test_point";
    d.position = Vecteur(0, 0, 10);
    d.direction = Vecteur(0, 0, 0);

    PointLight light(d, "test_point");

    PointOfImpact poi;
    poi.p = {0, 0, 0};
    poi.normal = {0, 0, 1};
    poi.material.color = Color(0, 1, 0);
    Color result = light.getIntensityAt(poi);

    cr_assert_float_eq(result.r, 0.0f, 0.001, "result.r devrait être 0.0");
    cr_assert_float_eq(result.g, 1.0f, 0.001, "result.g devrait être 1.0");
    cr_assert_float_eq(result.b, 0.0f, 0.001, "result.b devrait être 0.0");
}