cmake_minimum_required(VERSION 3.16)
project(RAYTRACER VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Compilation flags ===
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fPIC -fno-gnu-unique")

# === Dossiers ===
set(APP_DIR app)
set(INCLUDES_DIR includes)
set(SRC_DIR src)
set(UTILS_DIR utilitaires)
set(EXTRA_DIR src/extra)
set(PLUGINS_DIR plugins)

# === Headers communs ===
include_directories(
    ${INCLUDES_DIR}
    ${SRC_DIR}
    ${SRC_DIR}/base/camera
    ${SRC_DIR}/base/primitives
    ${SRC_DIR}/interfaces
    ${UTILS_DIR}
)

# === Fichiers sources principaux (hors plugins) ===
file(GLOB_RECURSE CORE_SOURCES
    ${SRC_DIR}/*.cpp
    ${UTILS_DIR}/*.cpp
)
# Exclure les plugins
foreach(file ${CORE_SOURCES})
    if(file MATCHES ".*/extra/.*")
        list(REMOVE_ITEM CORE_SOURCES ${file})
    endif()
endforeach()

# === Créer la bibliothèque statique raycore ===
add_library(raycore STATIC ${CORE_SOURCES})

target_include_directories(raycore PUBLIC
    ${INCLUDES_DIR}
    ${SRC_DIR}
    ${SRC_DIR}/base/camera
    ${SRC_DIR}/base/primitives
    ${SRC_DIR}/interfaces
    ${UTILS_DIR}
)

# === Lier SFML et config++ à raycore si nécessaire ===
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(raycore PUBLIC sfml-graphics sfml-window sfml-system config++)

# === Executable principal ===
add_executable(raytracer ${APP_DIR}/main.cpp)

target_link_libraries(raytracer PRIVATE raycore)

add_custom_command(TARGET raytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:raytracer> ${CMAKE_SOURCE_DIR}/raytracer
)

# === Tests avec Criterion ===
find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

if (CRITERION_FOUND)
    file(GLOB_RECURSE TEST_SOURCES test/*.cpp)

    add_executable(tests ${TEST_SOURCES})
    target_include_directories(tests PRIVATE ${CRITERION_INCLUDE_DIRS})
    target_link_libraries(tests PRIVATE raycore ${CRITERION_LIBRARIES})

    enable_testing()
    add_test(NAME CriterionTests COMMAND test)
else()
    message(WARNING "Criterion not found, tests will not be built")
endif()

# === Créer les plugins dynamiques (.so) ===
file(GLOB EXTRA_SOURCES "${EXTRA_DIR}/*.cpp")

foreach(plugin_src ${EXTRA_SOURCES})
    get_filename_component(plugin_name ${plugin_src} NAME_WE)

    add_library(${plugin_name} SHARED ${plugin_src})
    target_link_libraries(${plugin_name} PRIVATE raycore)

    set_target_properties(${plugin_name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PLUGINS_DIR}
    )
endforeach()

# === Cible de nettoyage complet ===
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
