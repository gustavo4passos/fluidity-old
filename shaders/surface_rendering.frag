#version 450 core

layout (location = 0) out vec4 frontSurface;

void main() 
{
    vec3 relativePos;
    relativePos.xy = gl_PointCoord.st;
    relativePos.xy = relativePos.xy * vec2(2, -2) + vec2(-1, 1);

    float magnitude = dot(relativePos.xy, relativePos.xy);
    if(magnitude > 1.0) discard;

    float frontSurfaceDepth = sqrt(1.0 - magnitude);

    relativePos.z = frontSurfaceDepth;  

    frontSurface = vec4(frontSurfaceDepth);
}