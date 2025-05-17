#include <criterion/criterion.h>
#include <cmath>
#include "../src/base/primitives/Cone.hpp"
#include "../includes/Ray.hpp"
#include "../includes/Vecteur.hpp"
#include "../includes/my.hpp"

struct DummyPointOfImpact : public PointOfImpact {};

Test(Cone, hit_intersects_inside_bounds) {
    dataPrimitive data{};
    data.radius = 1.0f;
    data.height = 2.0f;
    Cone cone(data, "test_cone");

    Ray ray(Vecteur{0, 0, -1}, Vecteur{0, 0, 1});
    PointOfImpact p;

    bool result = cone.hit(ray, 0.001f, 100.0f, p);
    cr_assert(result, "Le rayon devrait intersecter le cône.");
    cr_assert(p.t > 0.0f, "La valeur de t doit être positive.");
}

Test(Cone, hit_no_intersection) {
    dataPrimitive data{};
    data.radius = 1.0f;
    data.height = 2.0f;
    Cone cone(data, "test_cone");

    // Rayon parallèle à l'axe du cône, ne touche jamais
    Ray ray(Vecteur{5, 5, 1}, Vecteur{0, 0, 1});
    DummyPointOfImpact p;

    bool result = cone.hit(ray, 0.001f, 100.0f, p);
    cr_assert(!result, "Le rayon ne devrait pas intersecter le cône.");
}

Test(Cone, hit_out_of_height_bounds) {
    dataPrimitive data{};
    data.radius = 1.0f;
    data.height = 2.0f;
    Cone cone(data, "test_cone");

    // Rayon qui intersecte le cône mais hors de la hauteur [0, height]
    Ray ray(Vecteur{0, 0, 3}, Vecteur{0, 0, -1});
    DummyPointOfImpact p;

    bool result = cone.hit(ray, 0.001f, 100.0f, p);
    cr_assert(!result, "Le rayon intersecte le cône mais hors des bornes de hauteur.");
}

Test(Cone, hit_on_height_limit) {
    dataPrimitive data{};
    data.radius = 1.0f;
    data.height = 2.0f;
    Cone cone(data, "test_cone");

    // Rayon qui touche exactement la base supérieure du cône
    Ray ray(Vecteur{0, 0, 2}, Vecteur{0, 0, -1});
    DummyPointOfImpact p;

    bool result = cone.hit(ray, 0.001f, 100.0f, p);
    cr_assert(!result, "Le rayon touche la base supérieure, mais ne doit pas compter comme intersection valide.");
}
