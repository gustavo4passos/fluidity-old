cmake_minimum_required(VERSION 3.0.0)
project(opengl-fluidrendering)
set(ECECUTABLE_OUTPUT_PATH "./bin")

find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(CUDA 6.5 REQUIRED)

include_directories(src)
include_directories(./libs/cuda-common/inc)
include_directories(${CUDA_INCLUDE_DIRS})

link_directories(${CUDA_LIBRARY_DIRS})

file(GLOB RENDERING_SOURCES ./src/renderer/*.cpp)
# file(GLOB CUDA_COMMON_SOURCES ./libs/common/src/*.cpp)

file(GLOB SOURCES ./src/*.cpp)

cuda_add_library(particleSystemLib SHARED  
    ./src/simulation/particleSystem_cuda.cu
    ./src/simulation/particleSystem.cpp )

target_link_libraries(particleSystemLib ${CUDA_LIBRARIES} GLEW::GLEW)

add_executable(opengl-fluidrendering ${SOURCES} ${RENDERING_SOURCES})
target_link_libraries(opengl-fluidrendering GLEW::GLEW SDL2::SDL2main SDL2::SDL2 particleSystemLib)