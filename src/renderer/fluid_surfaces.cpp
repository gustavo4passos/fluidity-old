#include "fluid_surfaces.h"
#include "../utils/glcall.h"
#include "../utils/logger.h"

namespace fluidity
{
    FluidSurfaces::FluidSurfaces(unsigned width, unsigned height)
    :   m_frameBuffer(0),
        m_frontSurfaceBuffer(0),
        m_backSurfaceBuffer(0),
        m_bufferWidth(width),
        m_bufferHeight(height)
    {}

    
    bool FluidSurfaces::Init()
    {
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

        return true;
    }

}