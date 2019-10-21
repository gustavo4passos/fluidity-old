# Fluidity
Fluidity is a particle-based fluid renderer with two sided refractions implemented in OpenGL.

# How to build
The project uses vcpkg to manage dependencies. 
Use vcpkg to download and build SDL2, GLEW, freeglut and glm. The demo also requires the CUDA SDK.
To create a Makefile (GNU - Linux/ Windows) or a VS Project (Windows), create a folder called 'build', navigate to it and run: 
**LINUX:** 'cmake .. -DCMAKE_TOOLCHAIN_FILE=${vcpkg_path}/scripts/buildsystems/vcpkg.cmake'. 
**WINDOWS:** 'cmake -G "Visual Studio 16 2019" -A x64 .. -DCMAKE_TOOLCHAIN_FILE=${vcpkg_path}/scripts/buildsystems/vcpkg.cmake' 
Replace ${vcpkg_path} with the folder where vcpkg is located.
