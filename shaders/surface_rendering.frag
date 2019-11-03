#version 450 core

layout (location = 0) out vec4 frontSurface;
in vec4 vParticlePos;

void main() 
{
    vec3 relativePos;
    relativePos.xy = gl_PointCoord.st;
    relativePos.xy = relativePos.xy * vec2(2, -2) + vec2(-1, 1);

    float magnitude = dot(relativePos.xy, relativePos.xy);
    if(magnitude > 1.0) discard;

    float frontSurfaceDepth = sqrt(1.0 - magnitude);

    frontSurface = vec4(vParticlePos.z, -vParticlePos.z, 0.0, 1.0);
}