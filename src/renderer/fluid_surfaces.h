#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

namespace fluidity
{

class FluidSurfaces 
{
public:
    FluidSurfaces(unsigned width, unsigned height);

    auto Init() -> bool;

private:
    GLuint m_frameBuffer;
    GLuint m_frontSurfaceBuffer;
    GLuint m_backSurfaceBuffer;
    unsigned m_bufferWidth;
    unsigned m_bufferHeight;

};

}