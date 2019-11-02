#include "texture_renderer.h"
#include "../utils/glcall.h"

namespace fluidity
{
    TextureRenderer::TextureRenderer() 
    :   m_textureShader(nullptr),
        m_VAO(0),
        m_VBO(0),
        m_currentTexture(0)
    { }

    auto TextureRenderer::Init() -> bool
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
        GLCall(glGenVertexArrays(1, &m_VAO));
        GLCall(glGenBuffers(1, &m_VBO));

        GLCall(glBindVertexArray(m_VAO));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        GLCall(glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(screenQuadVertices), 
            (const GLvoid*)screenQuadVertices, 
            GL_STATIC_DRAW));

        GLCall(glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            4 * sizeof(GLfloat),
            (const GLvoid*) 0
        ));
        GLCall(glEnableVertexAttribArray(0));

        GLCall(glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            4 * sizeof(GLfloat),
            (const GLvoid*)(2 * sizeof(GLfloat))
        ));
        GLCall(glEnableVertexAttribArray(1));

        GLCall(glBindVertexArray(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        m_textureShader = new Shader(
            "../../shaders/texture_rendering.vert",
            "../../shaders/texture_rendering.frag");

        return true;

    }

    auto TextureRenderer::Render() -> void
    {
        m_textureShader->Bind();
        GLCall(glActiveTexture(GL_TEXTURE0));
        GLCall(glBindTexture(GL_TEXTURE_2D ,m_currentTexture));
        GLCall(glBindVertexArray(m_VAO));
        
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

        GLCall(glBindVertexArray(0));
        GLCall(glBindTexture(GL_TEXTURE_2D ,0));
        m_textureShader->Unbind();
    }
}