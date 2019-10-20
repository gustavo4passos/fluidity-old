#version 450 core

layout (location = 0) out float nearestSurface;

out vec4 outColor;

void main() 
{
    vec2 relativePos;
    relativePos = gl_PointCoord.st;
    relativePos = relativePos * vec2(2, -2) + vec2(-1, 1);

    float magnitude = dot(relativePos.xy, relativePos.xy);
    if(magnitude > 1.0) discard;

    float nearestSurface = sqrt(1.0 - magnitude);

    outColor = vec4(relativePos.xy, 0, 1);
}