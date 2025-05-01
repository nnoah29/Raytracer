#ifndef PLUGINSLOADER_HPP
#define PLUGINSLOADER_HPP

#include <string>
#include <stdexcept>
#include <dlfcn.h>
#include <filesystem>
#include <iostream>

#include "Factory.hpp"

class PluginsLoader {
    using PluginRegisterFunc = void (*)(Factory*);
    std::vector<void*> _handles;
    Factory* _factory{};

public:
    PluginsLoader() = default;
    PluginsLoader(char *argv[], Factory* f);
    ~PluginsLoader();

    void load(const std::string& path, Factory* factory);
};

#endif // PLUGINSLOADER_HPP
