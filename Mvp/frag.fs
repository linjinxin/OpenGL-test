#version 460 core

in vec2 coord;

uniform sampler2D texture;

out vec4 color;

void main()
{
    color = texture(texture, coord);
}