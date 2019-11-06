#version 450

in vec2 texCoord;
out vec4 fragmentColor;
uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, texCoord);
    fragmentColor = vec4(texColor.r * 0.2, 0, 0, 1.0);
    if(texColor.a > 0 && texColor.g < 0) fragmentColor.b = -texColor.g * 0.1;
}