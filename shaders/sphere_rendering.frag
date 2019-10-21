#version 450 core

layout (location = 0) out float nearestSurface;

out vec4 outColor;

void main() 
{
    const vec3 light = vec3(0.577, 0.577, 0.577);

    vec3 relativePos;
    relativePos.xy = gl_PointCoord.st;
    relativePos.xy = relativePos.xy * vec2(2, -2) + vec2(-1, 1);

    float magnitude = dot(relativePos.xy, relativePos.xy);
    if(magnitude > 1.0) discard;

    float nearestSurface = sqrt(1.0 - magnitude);

    relativePos.z = nearestSurface;
    relativePos = normalize(relativePos);
    float diffuse = max(0.0, dot(light, relativePos));
    outColor = vec4(vec3(0.8, 0.4, 0.1) * diffuse, 1.0);
    // outColor = vec4(relativePos.x, relativePos.y * 0.5, 0, 1);
}