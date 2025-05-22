/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 25/04/25.                                          
**         |___/ 
*/

#include <iostream>
#include <thread>

#include "../src/Factory.hpp"
#include "../src/PluginsLoader.hpp"
#include "../src/Raytracer.hpp"
#include "../src/Render.hpp"
#include "../src/SceneLoader.hpp"
/// Logique du programme
/// 1. La caméra génère un rayon → (x, y)
/// 2. Le rayon touche une primitive ? → Oui ? → continue
/// 3. Je regarde où ça touche et quelle est la normale
/// 4. J’utilise les lumières de la scène pour savoir
///     - Est-ce qu’on voit ce point ?
///     - Est-ce qu’il est dans l’ombre ?
///     - À quel point il est éclairé ?
/// 5. Je combine ça avec la couleur du matériau
/// 6. J’écris la couleur dans l’image finale
///

int main(int argc, char *argv[])
{
    try {
        if (argc < 2)
            throw std::runtime_error("Not enough arguments");
        Factory factory;
        PluginsLoader     loader_p(argv, &factory);
        const SceneLoader loader_s(std::string(argv[1]), argc);

        Scene scene = loader_s.createScene(factory);
        Render render(WEIGHT_IMG, HEIGHT_IMG, "exemple");
        Raytracer raytracer(scene, render);
        if (antialiasing) raytracer.render();
        else raytracer.renderLive();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

