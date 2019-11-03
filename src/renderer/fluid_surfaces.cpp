#include "fluid_surfaces.h"
#include "../utils/glcall.h"
#include "../utils/logger.h"
#include <glm/gtc/type_ptr.hpp>

namespace fluidity
{
    FluidSurfaces::FluidSurfaces(
        unsigned bufferWidth, 
        unsigned bufferHeight, 
        float pointRadius,
        float farPlane)
    :   m_surfacesShader(nullptr),
        m_currentVAO(0),
        m_frameBuffer(0),
        m_frontSurfaceBuffer(0),
        m_backSurfaceBuffer(0),
        m_currentNumberOfParticles(0),
        m_bufferWidth(bufferWidth),
        m_bufferHeight(bufferHeight),
        m_pointRadius(pointRadius),
        m_farPlane(farPlane)
    {}

    
    auto FluidSurfaces::Init() -> bool
    {
        m_surfacesShader = new Shader("../../shaders/surface_rendering.vert", "../../shaders/surface_rendering.frag");

        GLCall(glGenFramebuffers(1, &m_frameBuffer));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));

        GLCall(glGenTextures(1, &m_frontSurfaceBuffer));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_frontSurfaceBuffer));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_bufferWidth, m_bufferHeight, 0, GL_RGBA, GL_FLOAT, nullptr));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frontSurfaceBuffer, 0));

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_ERROR("Framebuffer is not complete.");
            return false;
        }
        
        unsigned attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        GLCall(glDrawBuffers(1, attachments));

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        m_surfacesShader->Bind();
        m_surfacesShader->SetUniform1f("pointRadius", m_pointRadius);
        m_surfacesShader->Unbind();

        return true;
    }

    auto FluidSurfaces::Render() -> void
    {
        GLboolean isBlendEnabled;
        GLboolean isDepthTestEnabled;

        GLCall(glGetBooleanv(GL_BLEND, &isBlendEnabled));
        GLCall(glGetBooleanv(GL_DEPTH_TEST, &isDepthTestEnabled));

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));
        GLCall(glClearColor(0.f, 0.f, 0.f, 0.f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunci(0, GL_ONE, GL_ONE_MINUS_CONSTANT_COLOR));
        GLCall(glBlendEquationi(0, GL_MAX));
        GLCall(glDisable(GL_DEPTH_TEST));

        GLfloat minz[] = { -m_farPlane, -m_farPlane, -m_farPlane, 0.f };
        GLCall(glClearTexImage(m_frontSurfaceBuffer, 0, GL_RGBA, GL_FLOAT, minz));
        GLCall(glActiveTexture(GL_TEXTURE0));
        m_surfacesShader->Bind();
        GLCall(glBindVertexArray(m_currentVAO));
        GLCall(glDrawArrays(GL_POINTS, 0, m_currentNumberOfParticles));

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
        GLCall(glBindVertexArray(0));
        m_surfacesShader->Unbind();

        if(!isBlendEnabled)
        {
            GLCall(glDisable(GL_BLEND));
        }
        if(isDepthTestEnabled) 
        {
            GLCall(glEnable(GL_DEPTH_TEST));
        }
    }

    auto FluidSurfaces::SetVAO(GLuint vao) -> void
    {
        m_currentVAO = vao;
    }

    auto FluidSurfaces::SetNumberOfParticles(unsigned n) -> void
    {
        m_currentNumberOfParticles = n;
    }

    auto FluidSurfaces::SetTransformationMatrices(
        const glm::mat4 &projectionMatrix,
        const glm::mat4 &view) -> void
    {
        m_surfacesShader->Bind();
        m_surfacesShader->SetUniformMat4("projection", glm::value_ptr(projectionMatrix));
        m_surfacesShader->SetUniformMat4("view", glm::value_ptr(view));
        m_surfacesShader->Unbind();

    }
}