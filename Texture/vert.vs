#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 coord;

out vec4 vcolor;
out vec2 vcoord;

void main()
{
    gl_Position = vec4(pos, 1.0f);
    vcolor = vec4(color, 1.0f);
    vcoord = coord;
}