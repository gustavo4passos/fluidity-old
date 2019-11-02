#include "fluid_renderer.h"
#include "../utils/glcall.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fluidity
{
    FluidRenderer::FluidRenderer(unsigned windowWidth, unsigned windowHeight, float pointRadius)
    :   Renderer(),
        m_fluidSurfaces(nullptr),
        m_textureRenderer(nullptr),
	    m_fluidShader("../../shaders/sphere_rendering.vert", "../../shaders/sphere_rendering.frag"),
        m_currentVAO(0),
        m_currentNumberOfParticles(0),
        m_windowWidth(windowWidth),
        m_windowHeight(windowHeight),
        m_aspectRatio((float) windowWidth / windowHeight),
        m_pointRadius(pointRadius)
    { }

    auto FluidRenderer::Clear() -> void
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    auto FluidRenderer::SetClearColor(float r, float g, float b, float a) -> void
    {
        glClearColor(r, g, b, a);
    }

    auto FluidRenderer::SetVAO(GLuint vao) -> void
    {
        m_currentVAO = vao;

        m_fluidSurfaces->SetVAO(vao);
    }

    auto FluidRenderer::SetNumberOfParticles(unsigned n) -> void
    {
        m_currentNumberOfParticles = n;

        m_fluidSurfaces->SetNumberOfParticles(n);
    }

    auto  FluidRenderer::Init() -> bool 
    {
        GLCall(glEnable(GL_PROGRAM_POINT_SIZE));

        m_fluidSurfaces = new FluidSurfaces(m_windowWidth, m_windowHeight, m_pointRadius);
        m_textureRenderer = new TextureRenderer();

        if(!m_fluidSurfaces->Init() || !m_textureRenderer->Init()) return false;  

        return true;
    }

    auto FluidRenderer::Render() -> void
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

        /*
        GLCall(glBindVertexArray(m_currentVAO));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDrawArrays(GL_POINTS, 0, m_currentNumberOfParticles));
        GLCall(glBindVertexArray(0));
        */

        m_fluidShader.Unbind();

        m_fluidSurfaces->SetTransformationMatrices(projectionMatrix, view);
        m_fluidSurfaces->Render();

        m_textureRenderer->SetTexture(m_fluidSurfaces->GetFrontSurface());
        Clear();
        m_textureRenderer->Render();
    }
}
