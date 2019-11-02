#pragma once

#include "renderer.h"
#include "shader.h"

namespace fluidity
{

class TextureRenderer : public Renderer
{
public:
    TextureRenderer();
        	
	TextureRenderer(const TextureRenderer&) = delete;

    auto Init()  -> bool;
    auto Clear() -> void;
    auto Render() -> void override;

    auto SetTexture(GLuint texture) { m_currentTexture = texture; }

private:
    Shader *m_textureShader;
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_currentTexture;
};

}
