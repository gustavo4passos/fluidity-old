#version 450 core

uniform sampler2D workingSurface;
uniform int kernelRadius;
layout (location = 0) out vec4 smoothedSurface;

in vec2 texCoord;


void main()
{
    vec2 ts = textureSize(workingSurface, 0);

    for(int i = -kernelRadius; i <= kernelRadius; i++)
    {
        for(int j = -kernelRadius; j <= kernelRadius; j++)
        {
            vec4 texel = texture(
                workingSurface,
                texCoord + vec2(i, j) * (1.0 / ts));
            if(texel.a == 0.0) texel = vec4(0.0);
            smoothedSurface += texel;
        }  
    }
    smoothedSurface /= (kernelRadius * kernelRadius * 4);
}