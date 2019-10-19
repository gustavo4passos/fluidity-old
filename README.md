# Fluidity
Fluidity is a particle-based fluid renderer with two sided refractions implemented in OpenGL.

# How to build
The project uses vcpkg to manage dependencies. 
With vcpkg, you will need SDL2, GLEW and freeglut installed. You will also need the CUDA SDK.
To create a Makefile (GNU - Linux/ Windows) or a VS Project (Windows), create a folder called 'build', navigate to it and run 'cmake .. -DCMAKE_TOOLCHAIN_FILE=${vcpkg_path}/scripts/buildsystems/vcpkg.cmake'. replace ${vcpkg_path} with the folder where vcpkg is installed.