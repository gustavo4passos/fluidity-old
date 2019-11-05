#pragma once

#include "shader.h"
#include <glm/glm.hpp>

namespace fluidity
{

class FluidSurfaceRenderers 
{
public:
    FluidSurfaceRenderers(
        unsigned bufferWidth, 
        unsigned bufferHeight, 
        float pointRadius,
        float farPlane);

    auto Init() -> bool;
    auto Render() -> void;

    auto GetFrontSurface() { return m_frontSurfaceBuffer; }

    auto SetVAO(GLuint vao) -> void;
    auto SetNumberOfParticles(unsigned n) -> void;
    auto SetTransformationMatrices(const glm::mat4 &projectionMatrix, const glm::mat4 &view) -> void;

private:
    Shader *m_surfacesShader;

    GLuint m_currentVAO;  
    GLuint m_frameBuffer;
    GLuint m_frontSurfaceBuffer;
    GLuint m_backSurfaceBuffer;

    unsigned m_currentNumberOfParticles;
    unsigned m_bufferWidth;
    unsigned m_bufferHeight;

    float m_pointRadius;
    float m_farPlane;
};

}