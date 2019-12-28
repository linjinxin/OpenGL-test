#version 460 core

in vec4 vcolor;
in vec2 vcoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

out vec4 color;

void main()
{
    // color = texture(Texture, vcoord) * vcolor;
    color = mix(texture(Texture1, vcoord), texture(Texture2, vcoord), 0.5) * vcolor;
}