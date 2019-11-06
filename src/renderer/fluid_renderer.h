#pragma once

#include "renderer.h"
#include "shader.h"
#include "fluid_surfaces_renderer.h"
#include "surface_smoothing_pass.h"
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
    FluidSurfaceRenderers *m_fluidSurfaces;
    SurfaceSmoothingPass* m_surfaceSmoothingPass;
    TextureRenderer *m_textureRenderer;
    GLuint m_currentVAO;
    unsigned m_currentNumberOfParticles;
    unsigned m_windowWidth;
    unsigned m_windowHeight;

    float m_aspectRatio;
    float m_pointRadius;

    const GLfloat NEAR_PLANE = 0.1f;
    const GLfloat FAR_PLANE  = 100.f;
};

}
