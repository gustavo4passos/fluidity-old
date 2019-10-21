#pragma once

namespace fluidity
{

class Renderer 
{
public:
	Renderer() { }
    virtual auto Clear()  -> void = 0;
	virtual auto Render() -> void = 0;
    virtual auto SetClearColor(
		float r, 
		float g, 
		float b, 
		float a) -> void = 0;
};

}
