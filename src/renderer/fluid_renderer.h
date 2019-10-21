#pragma once
#include "renderer.h"
#include "shader.h"


namespace fluidity
{

class FluidRenderer : public Renderer
{
public:
    explicit FluidRenderer(
        float aspectRatio = 1920 / 1080.f, 
        float pointRadius  = 6.f);
	
	FluidRenderer(const FluidRenderer&) = delete;

    auto Init()  -> bool;
    auto Clear() -> void override;
    auto SetVAO(GLuint vao) -> void;
    auto SetNumberOfParticles(unsigned n) -> void;
    auto Render() -> void override;
    auto SetClearColor(float r, float g, float b, float a) -> void override;

private:
    Shader m_fluidShader;
    GLuint m_currentVAO;
    unsigned m_currentNumberOfParticles;

    float m_aspectRatio;
    float m_pointRadius;
};

}
