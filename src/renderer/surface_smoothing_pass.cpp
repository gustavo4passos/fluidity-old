#include "surface_smoothing_pass.h"
#include "../utils/logger.h"
#include "../utils/glcall.h"
#include <assert.h>

namespace fluidity
{
    SurfaceSmoothingPass::SurfaceSmoothingPass(
        const unsigned bufferWidth,
        const unsigned bufferHeight,
        const unsigned kernelRadius,
        const unsigned nIterations)
    :   m_bufferWidth(bufferWidth),
        m_bufferHeight(bufferHeight),
        m_kernelRadius(kernelRadius),
        m_nIterations(nIterations),
        m_fbo(0),
        m_unfilteredSurfaces(0),
        m_currentWorkingSurfaces(0),
        m_smoothedSurfaces(0),
        m_bilateralFilter(nullptr)
    { }

    auto SurfaceSmoothingPass::Init() -> bool
    {
        GLfloat screenQuadVertices[] = 
        {
            -1.f,  1.f, 0.f, 1.f,
             1.f,  1.f, 1.f, 1.f,
            -1.f, -1.f, 0.f, 0.f,
             1.f,  1.f, 1.f, 1.f,
            -1.f, -1.f, 0.f, 0.f,
             1.f, -1.f, 1.f, 0.f
        };
        
        GLCall(glGenBuffers(1, &m_screenQuadVbo));
        GLCall(glGenVertexArrays(1, &m_screenQuadVao));
        GLCall(glBindVertexArray(m_screenQuadVao));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_screenQuadVbo));
        GLCall(glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(screenQuadVertices), 
            screenQuadVertices, 
            GL_STATIC_DRAW));


        GLCall(glVertexAttribPointer(
            0, 
            2, 
            GL_FLOAT, 
            GL_FALSE, 
            sizeof(GLfloat) * 4, 
            (const GLvoid*)0));
        GLCall(glEnableVertexAttribArray(0));

        GLCall(glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(GLfloat) * 4,
            (const GLvoid*)(2 * sizeof(GLfloat))));
        GLCall(glEnableVertexAttribArray(1));

        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        GLCall(glGenFramebuffers(1, &m_fbo));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));

        GLCall(glGenTextures(1, &m_currentWorkingSurfaces));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_currentWorkingSurfaces));
        GLCall(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA32F, 
            m_bufferWidth, 
            m_bufferHeight,
            0,
            GL_RGBA,
            GL_FLOAT,
            nullptr));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));    
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));    

        GLCall(glGenTextures(1, &m_smoothedSurfaces));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_smoothedSurfaces));
        GLCall(glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA32F, 
            m_bufferWidth, 
            m_bufferHeight,
            0,
            GL_RGBA,
            GL_FLOAT,
            nullptr));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));    
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));    
        // GLCall(glFramebufferTexture2D(
        //     GL_FRAMEBUFFER,
        //     GL_COLOR_ATTACHMENT0,
        //     GL_TEXTURE_2D,
        //     m_smoothedSurfaces,
        //     0));

        // if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        // {
        //     LOG_ERROR("Framebuffer is not complete.");
        //     return false;
        // }

        unsigned attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        
        GLCall(glDrawBuffers(1, attachments));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        m_bilateralFilter = new Shader(
            "../../shaders/texture_rendering.vert",
            "../../shaders/bilateral_filter.frag");

        return true;
    }

    auto SurfaceSmoothingPass::SetUnfilteredSurfaces(const GLuint unfilteredSurfaces) -> void
    {
        m_unfilteredSurfaces = unfilteredSurfaces;
    }

    auto SurfaceSmoothingPass::Render() -> void
    {
        assert(m_bilateralFilter != nullptr);

        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
        m_bilateralFilter->Bind();
        m_bilateralFilter->SetInt("kernelRadius", m_kernelRadius);

        GLCall(glBindVertexArray(m_screenQuadVao));
        GLCall(glActiveTexture(GL_TEXTURE0));
        glBindTexture(GL_TEXTURE_2D, m_unfilteredSurfaces);

        GLCall(glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D,
                m_smoothedSurfaces,
                0));

        for(unsigned i = 0; i < m_nIterations; i++)
        {
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

            glBindTexture(GL_TEXTURE_2D, 0);
            GLCall(glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D,
                0,
                0));

            InvertWorkingAndSmoothedSurfaces();
            GLCall(glBindTexture(GL_TEXTURE_2D, m_currentWorkingSurfaces));
            GLCall(glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D,
                m_smoothedSurfaces,
                0));
        }

        InvertWorkingAndSmoothedSurfaces();
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        GLCall(glBindVertexArray(0));
        m_bilateralFilter->Unbind();
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    auto SurfaceSmoothingPass::InvertWorkingAndSmoothedSurfaces() -> void
    {
        GLuint tempTex = m_currentWorkingSurfaces;
        m_currentWorkingSurfaces = m_smoothedSurfaces;
        m_smoothedSurfaces = tempTex;
    }
};