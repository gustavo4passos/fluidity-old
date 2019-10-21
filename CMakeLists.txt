cmake_minimum_required(VERSION 3.0.0)
project(fluidity)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(SDL2 2.0 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(CUDA 6.5 REQUIRED)
find_package(GLUT REQUIRED)

include_directories(src)
include_directories(./libs/cuda-common/inc)
include_directories(./libs/cuda-simulation/src)
include_directories(${CUDA_INCLUDE_DIRS})

link_directories(${CUDA_LIBRARY_DIRS})

file(GLOB RENDERING_SOURCES ./src/renderer/*.cpp)
file(GLOB SIMULATION_SOURCES ./src/simulation/*.cpp)
file(GLOB SOURCES ./src/*.cpp)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

cuda_add_library(particleSystemLib SHARED  
./libs/cuda-simulation/src/particleSystem_cuda.cu
./libs/cuda-simulation/src/particleSystem.cpp )

set_property(TARGET particleSystemLib 
             PROPERTY CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(particleSystemLib ${CUDA_LIBRARIES} GLEW::GLEW GLUT::GLUT)

add_executable(fluidity
    ${SOURCES}
    ${RENDERING_SOURCES} 
    ${SIMULATION_SOURCES})

target_link_libraries(fluidity GLEW::GLEW SDL2::SDL2main SDL2::SDL2 particleSystemLib)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    target_compile_options(fluidity PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(fluidity PRIVATE /EHsc /MTd /W2 /c)
    target_compile_definitions(fluidity PRIVATE WIN_EXPORT)
endif()