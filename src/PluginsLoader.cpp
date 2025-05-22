/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 28/04/25.                                          
**         |___/ 
*/

#include "PluginsLoader.hpp"

PluginsLoader::PluginsLoader(char *argv[], Factory* f) {
    _factory = f;
    int pos = -1;
    for (int i = 0; argv[i] != nullptr; i++)
    {
        if (std::string(argv[i]) == "-p") pos = i + 1;
        if (std::string(argv[i]) == "-l" || std::string(argv[i]) == "--live") antialiasing = false;
    }
    if (pos == -1) return;
    if (argv[pos] == nullptr) throw std::runtime_error("No Plugins Found");
    for (int i = pos; argv[i] != nullptr; i++) {
        if (argv[i][0] == '-') break;
        load(argv[i], f);
    }
}

PluginsLoader::~PluginsLoader() {
    _factory->unregisterPrimitive();
    for (void* handle : _handles) {
        if (handle) {
            dlclose(handle);
        }
    }
}

void PluginsLoader::load(const std::string& path, Factory* factory)
{
    if (!std::filesystem::exists(path)) throw std::runtime_error("No Plugins Found");
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        const char* dlopen_error = dlerror();
        std::string error_msg = "❌ Failed to load plugin: " + path;
        if (dlopen_error) {
            error_msg += " (dlerror: ";
            error_msg += dlopen_error;
            error_msg += ")";
        }
        throw std::runtime_error(error_msg);
    }

    const auto registerFunc = reinterpret_cast<PluginRegisterFunc>(dlsym(handle, "RegisterPlugin"));
    if (!registerFunc) {
        dlclose(handle);
        throw std::runtime_error("❌ Symbol 'RegisterPlugin' not found in plugin: " + path);
    }

    // Appeler le plugin pour qu'il s'enregistre lui-même dans la factory
    registerFunc(factory);
    _handles.push_back(handle);
}