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

# === Executable principal ===
add_executable(raytracer ${CORE_SOURCES}
        src/Scene.hpp
        src/SceneLoader.hpp
        src/extra/cone.hpp
        src/extra/cylinder.hpp
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
        src/base/primitives/Cone.cpp
        src/base/primitives/Cone.hpp)

add_custom_command(TARGET raytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:raytracer> ${CMAKE_SOURCE_DIR}/raytracer
)


# === SFML ===
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)


# === Criterion Unit Tests ===
# find_package(PkgConfig REQUIRED)
# if (NOT criterion_FOUND)
#     message(WARNING "Criterion not found, tests will not be built")
# endif()

# file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

# set(TESTABLE_CORE_SOURCES ${CORE_SOURCES})
# list(REMOVE_ITEM TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp)

# add_executable(tests
#         ${TESTABLE_CORE_SOURCES}
#         ${TEST_SOURCES}
#         tests/cone_test.cpp
# )

# target_include_directories(tests PRIVATE ${CRITERION_INCLUDE_DIRS})

# target_link_libraries(tests PRIVATE ${CRITERION_LIBRARIES})

# target_link_libraries(tests PRIVATE sfml-graphics sfml-window sfml-system)

# target_link_libraries(tests PRIVATE config++)

# enable_testing()
# add_test(NAME CriterionTests COMMAND tests)


# === Créer les plugins dynamiques (.so) ===
foreach(plugin_src ${EXTRA_SOURCES})
    get_filename_component(plugin_name ${plugin_src} NAME_WE)
    add_library(${plugin_name} SHARED ${plugin_src}
            src/extra/cone.hpp
            src/extra/cylinder.hpp
            src/interfaces/ICamera.hpp
            src/interfaces/ILight.hpp
            src/interfaces/IPrimitive.hpp
            src/interfaces/APrimitive.hpp
            includes/Color.hpp
            includes/my.hpp
            includes/Ray.hpp
            includes/Vecteur.hpp
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
            src/base/primitives/Cone.cpp
            src/base/primitives/Cone.hpp
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

