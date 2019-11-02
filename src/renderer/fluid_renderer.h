#pragma once

#include "renderer.h"
#include "shader.h"
#include "fluid_surfaces.h"
#include "texture_renderer.h"
#include "../utils/export_directives.h"

namespace fluidity
{

class EXPORT FluidRenderer : public Renderer
{
public:
    FluidRenderer(unsigned windowWidth, unsigned windowHeight, float pointRadius);
        	
	FluidRenderer(const FluidRenderer&) = delete;

    auto Init()  -> bool;
    auto Clear() -> void;
    auto SetVAO(GLuint vao) -> void;
    auto SetNumberOfParticles(unsigned n) -> void;
    auto Render() -> void override;
    auto SetClearColor(float r, float g, float b, float a) -> void;

private:
    FluidSurfaces *m_fluidSurfaces;
    TextureRenderer *m_textureRenderer;
    Shader m_fluidShader;
    GLuint m_currentVAO;
    unsigned m_currentNumberOfParticles;
    unsigned m_windowWidth;
    unsigned m_windowHeight;

    float m_aspectRatio;
    float m_pointRadius;
};

}
