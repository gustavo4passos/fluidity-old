#pragma once
#include "renderer.h"

namespace fluidity
{

class FluidRenderer : public Renderer
{
public:
    explicit FluidRenderer() { }

    bool Init();
    void Clear() override;
    void SetClearColor(float r, float g, float b, float a) override;
};

}