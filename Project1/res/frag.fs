#version 440 core

in vec2 TexCoord;
out vec4 finalColor;
uniform sampler2D Texture;

void main()
{
	finalColor = texture(Texture, TexCoord);
}
