cmake_minimum_required(VERSION 3.0.0)
project(opengl-fluidrendering)
find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

include_directories(src)
file(GLOB RENDERING_SOURCES ./src/renderer/*.cpp)
file(GLOB SOURCES ./src/*.cpp)

add_executable(opengl-fluidrendering ${SOURCES} ${RENDERING_SOURCES})
target_link_libraries(opengl-fluidrendering PRIVATE GLEW::GLEW SDL2::SDL2main SDL2::SDL2)