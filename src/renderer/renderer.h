#pragma once

namespace fluidity
{

class Renderer 
{
public:
    virtual void Clear() = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
};

}