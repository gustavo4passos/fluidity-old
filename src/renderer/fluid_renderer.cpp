#include "fluid_renderer.h"
#include "../utils/glcall.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl.h>

namespace fluidity
{
    FluidRenderer::FluidRenderer(float aspectRatio, float pointRadius)
    : Renderer(),
	m_fluidShader("../../shaders/sphere_rendering.vert", "../../shaders/sphere_rendering.frag"),
    m_currentVAO(0),
    m_currentNumberOfParticles(0),
    m_aspectRatio(aspectRatio),
    m_pointRadius(pointRadius)
    { 
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
    }

    void FluidRenderer::Clear() 
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.f), m_aspectRatio, 0.1f, 100.f);
        m_fluidShader.SetUniformMat4("projection", glm::value_ptr(projectionMatrix));
        m_fluidShader.SetUniform1f("pointRadius", m_pointRadius);

        // float radius = 0.001;
        // float camX = std::sin(SDL_GetTicks() * radius);
        // float camZ = std::cos(SDL_GetTicks() * radius);

        glm::vec3 cameraPos = glm::vec3(3, 0.f, -1.f);
        glm::vec3 cameraTarget = glm::vec3(0.f, -0.5f, 0.f);
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
        m_fluidShader.SetUniformMat4("view", glm::value_ptr(view));

        GLCall(glBindVertexArray(m_currentVAO));
        GLCall(glDrawArrays(GL_POINTS, 0, m_currentNumberOfParticles));
        GLCall(glBindVertexArray(0));
        m_fluidShader.Unbind();
    }
}
