#pragma once
#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* path, int name);
	~Texture();
	void bind(GLint location, GLint index);

	inline GLuint getTexObject() { return TexObject; }
	inline GLint getTexName() { return TexName; }

private:
	GLuint TexObject;
	GLint TexName;
};

