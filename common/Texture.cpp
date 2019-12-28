#include "Texture.h"
#include "SOIL.h"

Texture::Texture(const char* path, int name)
{
	int width, height;
	unsigned char *image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	this->TexName = name;
	glGenTextures(name, &TexObject);
	glBindTexture(GL_TEXTURE_2D, TexObject);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLfloat color[] = { 1.0f,0.0f,0.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

Texture::~Texture()
{
	glDeleteTextures(TexName,&TexObject);
}

void Texture::bind(GLint location, GLint index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, TexObject);
	glUniform1i(location, index);
}
