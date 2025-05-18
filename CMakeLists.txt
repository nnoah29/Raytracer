cmake_minimum_required(VERSION 3.16)
project(RAYTRACER VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PROGRESS_REPORT ON)


# === Options de compilation ===
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fPIC -fno-gnu-unique")


# === Couleurs dans le terminal ===
if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    set(CMAKE_COLOR_MAKEFILE ON)
endif()

# === Chemins ===
set(APP_DIR app)
set(INCLUDES_DIR includes)
set(SRC_DIR src)
set(UTILS_DIR utilitaires)
set(EXTRA_DIR src/extra)
set(PLUGINS_DIR plugins)

# === Inclure les headers ===
include_directories(
        ${INCLUDES_DIR}
        ${SRC_DIR}/base/camera
        ${SRC_DIR}/base/primitives
        ${SRC_DIR}/interfaces
        ${UTILS_DIR}
)

# === Définir les sources du Core (hors src/extra) ===
file(GLOB_RECURSE CORE_SOURCES
        ${APP_DIR}/*.cpp
        ${SRC_DIR}/base/**/*.cpp
        ${SRC_DIR}/interfaces/*.cpp
        ${UTILS_DIR}/*.cpp
        ${SRC_DIR}/*.cpp
)
# Exclure les fichiers de src/extra
foreach(file ${CORE_SOURCES})
    if(file MATCHES ".*/extra/.*")
        list(REMOVE_ITEM CORE_SOURCES ${file})
    endif()
endforeach()

# === Définir les sources pour les plugins dynamiques ===
file(GLOB_RECURSE EXTRA_SOURCES
        ${EXTRA_DIR}/*.cpp
)

# === Définir les sources testables (pour les tests unitaires) ===
file(GLOB_RECURSE TESTABLE_SOURCES
        ${SRC_DIR}/base/**/*.cpp
        ${SRC_DIR}/interfaces/*.cpp
        ${UTILS_DIR}/*.cpp
)
# Ajouter explicitement Factory.cpp aux sources testables
list(APPEND TESTABLE_SOURCES ${SRC_DIR}/Factory.cpp)
# Ajouter d'autres fichiers du répertoire src si nécessaire
list(APPEND TESTABLE_SOURCES ${SRC_DIR}/Scene.cpp)
list(APPEND TESTABLE_SOURCES ${SRC_DIR}/SceneLoader.cpp)
list(APPEND TESTABLE_SOURCES ${SRC_DIR}/Render.cpp)

# === Executable principal ===
add_executable(raytracer ${CORE_SOURCES}
        src/Scene.hpp
        src/SceneLoader.hpp
        src/extra/Cone.hpp
        src/extra/Cylinder.hpp
        src/base/camera/Camera.hpp
        src/interfaces/ICamera.hpp
        src/interfaces/ILight.hpp
        src/interfaces/IPrimitive.hpp
        src/PluginsLoader.cpp
        src/PluginsLoader.hpp
        src/Factory.cpp
        src/Factory.hpp
        src/interfaces/APrimitive.hpp
        includes/Color.hpp
        includes/my.hpp
        includes/Ray.hpp
        includes/Vecteur.hpp
        src/Raytracer.cpp
        src/Raytracer.hpp
        includes/conf.hpp
        includes/Material.hpp
        src/base/camera/Camera.cpp
        src/base/camera/Camera.hpp
        src/base/primitives/Plane.hpp
        src/interfaces/ALight.hpp
        src/base/lights/PointLight.cpp
        src/base/lights/PointLight.hpp
        src/base/lights/DirectionalLight.cpp
        src/base/lights/DirectionalLight.hpp
)

add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:raytracer> ${CMAKE_SOURCE_DIR}/raytracer
)


# === SFML ===
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)

#=== units tests ====
find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

if (CRITERION_FOUND)
    # Exécutable de test
    add_executable(tests
            tests/lights_test.cpp
            tests/factory_test.cpp
            tests/camera_test.cpp
            tests/scene_test.cpp  # Ajout du nouveau fichier de test
            ${TESTABLE_SOURCES}
    )

    target_include_directories(tests PRIVATE
            ${CRITERION_INCLUDE_DIRS}
            ${INCLUDES_DIR}
            ${SRC_DIR}/base/camera
            ${SRC_DIR}/base/primitives
            ${SRC_DIR}/interfaces
            ${UTILS_DIR}
    )

    target_link_libraries(tests PRIVATE
            ${CRITERION_LIBRARIES}
            sfml-graphics
            sfml-window
            sfml-system
            config++
    )

    enable_testing()
    add_test(NAME CriterionTests COMMAND tests)
else()
    message(WARNING "Criterion not found, tests will not be built")
endif()


# === Créer les plugins dynamiques (.so) ===
foreach(plugin_src ${EXTRA_SOURCES})
    get_filename_component(plugin_name ${plugin_src} NAME_WE)
    add_library(${plugin_name} SHARED ${plugin_src}
            includes/Vecteur.hpp
            src/extra/Cone.hpp
            src/extra/Cylinder.hpp
            src/interfaces/ICamera.hpp
            src/interfaces/ILight.hpp
            src/interfaces/IPrimitive.hpp
            src/interfaces/APrimitive.hpp
            includes/Color.hpp
            includes/my.hpp
            includes/Ray.hpp
            src/Factory.cpp
            src/Factory.hpp
            includes/conf.hpp
            includes/Material.hpp
            src/base/primitives/Plane.hpp
            src/interfaces/ALight.hpp
            src/base/lights/PointLight.cpp
            src/base/lights/PointLight.hpp
            src/base/lights/DirectionalLight.cpp
            src/base/lights/DirectionalLight.hpp
            utilitaires/vector_operation.cpp
            utilitaires/utilitaires.cpp
    )
    set_target_properties(${plugin_name} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PLUGINS_DIR}
    )
endforeach()

# === Cible cleanl ===
add_custom_target(fclean
        COMMAND ${CMAKE_COMMAND} --build . --target clean
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PLUGINS_DIR}
        COMMAND ${CMAKE_COMMAND} -E remove raytracer
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/raytracer
        COMMENT "🧹 [FCLEAN] Full clean : build files, plugins, binaries removed."
)