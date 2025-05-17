#include <criterion/criterion.h>
#include "../src/Factory.hpp"


Test(Dummy, always_pass) {
    cr_assert(1 == 1, "Ce test doit toujours passer.");
}

Test(Factory, can_register_and_create_custom) {
    Factory f;
    f.registerPrimitive("custom", [](dataPrimitive d, const std::string& s) -> std::shared_ptr<IPrimitive> {
        (void)d;
        (void)s;
        return nullptr;
    });
    dataPrimitive d{};
    auto prim = f.Primitive("custom", d);
    cr_assert(prim == nullptr, "La primitive 'custom' doit être nullptr dans ce test.");
}