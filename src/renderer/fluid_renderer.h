#pragma once
#include "renderer.h"
#include "shader.h"


namespace fluidity
{

class FluidRenderer : public Renderer
{
public:
    explicit FluidRenderer();

    bool Init();
    void Clear() override;
    void SetClearColor(float r, float g, float b, float a) override;
    void SetVAO(GLuint vao);
    void SetNumberOfParticles(unsigned n);
    void Render();

private:
    Shader m_fluidShader;
    GLuint m_currentVAO;
    unsigned m_currentNumberOfParticles;
};

}