#version 450

in vec2 texCoord;
out vec4 fragmentColor;
uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, texCoord);
    fragmentColor = vec4(0.2, 0, texColor.r - 3, 1.0);
    if(texColor.a > 0) fragmentColor.b = -texColor.g - 2.3;
}