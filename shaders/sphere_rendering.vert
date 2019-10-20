#version 450 core

layout (location = 0) in vec4 particlePos;

// uniform float radius;
// uniform float scale;

void main() 
{
    // float dist = length(particlePos.xyz);
    // gl_PointSize = radius * (scale / dist);
    gl_PointSize = 5.f;
    gl_Position = particlePos + 0.5;
}
