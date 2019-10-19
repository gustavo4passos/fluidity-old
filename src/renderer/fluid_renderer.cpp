#include "fluid_renderer.h"
#include <GL/gl.h>

namespace fluidity
{
    void FluidRenderer::Clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void FluidRenderer::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }
}