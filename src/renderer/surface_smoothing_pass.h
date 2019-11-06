#pragma once
#include "renderer.h"
#include "shader.h"

namespace fluidity
{

class SurfaceSmoothingPass
{
public:
    SurfaceSmoothingPass(
        const unsigned bufferWidth,
        const unsigned bufferHeight,
        const unsigned kernelRadius = 4,
        const unsigned nIterations = 20);
    
    SurfaceSmoothingPass(const SurfaceSmoothingPass&) = delete;

    auto Init()   -> bool;
    auto Render() -> void;
    auto GetSmoothedSurfaces() -> GLuint { return m_smoothedSurfaces; }
    auto SetUnfilteredSurfaces(const GLuint unfilteredSurfaces) -> void;

private:
    auto InvertWorkingAndSmoothedSurfaces() -> void;
    
    unsigned m_screenQuadVbo;
    unsigned m_screenQuadVao;
    unsigned m_bufferWidth;
    unsigned m_bufferHeight;
    unsigned m_kernelRadius;
    unsigned m_nIterations;

    GLuint m_fbo;
    GLuint m_unfilteredSurfaces;
    GLuint m_currentWorkingSurfaces;
    GLuint m_smoothedSurfaces;

    Shader* m_bilateralFilter;

};

};