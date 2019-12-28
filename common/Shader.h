#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL\glew.h>
#include <GL\glut.h>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void use();
	GLuint getProgram();

private:
	GLuint glProgram;

public:
	static const int SUCCESS = 1;
	static const int COMPILE_ERROR = 2;
	static const int LINK_ERROR = 3;
};

#endif // !__SHADER_H__

