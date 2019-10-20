#include "fluid_renderer.h"
#include "../utils/glcall.h"
#include <GL/gl.h>

namespace fluidity
{
    FluidRenderer::FluidRenderer()
    : m_fluidShader("../../shaders/sphere_rendering.vert", "../../shaders/sphere_rendering.frag"),
    m_currentVAO(0),
    m_currentNumberOfParticles(0)
    { 
        GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
    }

    void FluidRenderer::Clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void FluidRenderer::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void FluidRenderer::SetVAO(GLuint vao)
    {
        m_currentVAO = vao;
    }

    void FluidRenderer::SetNumberOfParticles(unsigned n)
    {
        m_currentNumberOfParticles = n;
    }

    void FluidRenderer::Render()
    {
        m_fluidShader.Bind();
        GLCall(glBindVertexArray(m_currentVAO));
        GLCall(glDrawArrays(GL_POINTS, 0, m_currentNumberOfParticles));
        GLCall(glBindVertexArray(0));
        m_fluidShader.Unbind();
    }
}