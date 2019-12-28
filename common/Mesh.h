#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	Mesh(GLfloat* vertices, GLint vao_name, GLint vbo_name, GLint vertex_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens);
	Mesh(GLfloat* vertices, GLuint* indices, GLint vao_name, GLint vbo_name, GLint ebo_name, GLint vertex_count, GLint index_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens);
	~Mesh();

	void bind();

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLsizei VAO_name;
	GLsizei VBO_name;
	GLsizei EBO_nmae;
};

