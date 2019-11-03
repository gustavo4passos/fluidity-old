#version 450 core

layout (location = 0) in vec4 particlePos;
out vec4 vParticlePos;

uniform mat4 projection;
uniform mat4 view;

uniform float pointRadius;
// uniform float scale;

void main() 
{
    // float dist = length(particlePos.xyz);
    // gl_PointSize = radius * (scale / dist);
    gl_PointSize = pointRadius;
    gl_Position =  projection * view * particlePos;
    vParticlePos = gl_Position;
}
