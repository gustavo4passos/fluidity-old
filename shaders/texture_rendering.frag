#version 450

in vec2 texCoord;
out vec4 fragmentColor;
uniform sampler2D tex;

void main()
{
    fragmentColor = texture(tex, texCoord);
}