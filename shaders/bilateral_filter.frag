#version 450 core

uniform sampler2D workingSurface;
uniform int kernelRadius;
layout (location = 0) out vec4 smoothedSurface;

in vec2 texCoord;

vec4 getValidTexel(sampler2D tex, vec2 coordinates)
{
    vec4 texel = texture(tex, coordinates);
    if(texel.a < 1.0) return vec4(0, 0, 0, 1);

    return texel;
}

vec4 pow4(vec4 base, int exponent)
{
    return vec4(pow(base.x, exponent), pow(base.y, exponent), pow(base.z, exponent), pow(base.w, exponent));
}


float w1(int m, int n)
{
    float sigma1 = kernelRadius / (2 * sqrt(2));
    return exp(-((pow(m, 2) + pow(n, 2)) / (2 * pow(sigma1, 2))));
}

vec4 w2(int m, int n, vec2 texSize)
{
    //TODO: 1 should be the particle radius
    float sigma2 = 2 * sqrt(2 * 0.5);
    return exp(
        - (pow4((getValidTexel(workingSurface, texCoord) - 
            getValidTexel(workingSurface, texCoord + vec2(m, n) * texSize)), 2) / pow(sigma2, 2)));
}


void main()
{
    vec2 ts = textureSize(workingSurface, 0);

    for(int i = -kernelRadius; i <= kernelRadius; i++)
    {
        for(int j = -kernelRadius; j <= kernelRadius; j++)
        {
            vec4 texel = getValidTexel(
                workingSurface,
                texCoord + vec2(i, j) * (1.0 / ts));
            smoothedSurface += texel;
        }  
    }

    smoothedSurface /= (kernelRadius * kernelRadius * 4);

    // vec4 numerator = vec4(0.0);
    // vec4 denominator = vec4(0.0);

    // for(int i = -kernelRadius; i <= kernelRadius; i++)
    // {
    //     for(int j = -kernelRadius; j <= kernelRadius; j++)
    //     {
    //        numerator += 
    //         getValidTexel(workingSurface, texCoord + vec2(i, j) * ts) * w1(i, j) * w2(i, j, ts);
    //         denominator += (w1(i, j) * w2(i, j, ts));
    //     }  
    // }

    // smoothedSurface = numerator / denominator;
}