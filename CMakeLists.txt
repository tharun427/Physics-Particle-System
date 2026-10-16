cmake_minimum_required(VERSION 3.15)

project(Physics_Particles_Engine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(Simulation 
main.cpp 
src/vec2.cpp 
src/particle.cpp 
)

target_include_directories(Simulation PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(raylib REQUIRED)
if(raylib_found)
    target_link_libraries(Simulation PRIVATE raylib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib)
    target_link_libraries(Simulation PRIVATE PkgConfig::RAYLIB)
endif()