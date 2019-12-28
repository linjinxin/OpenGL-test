#include "Mesh.h"

Mesh::Mesh(GLfloat* vertices, GLint vao_name, GLint vbo_name, GLint vertex_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens)
{
	glGenVertexArrays(vao_name, &VAO);
	glGenBuffers(vbo_name, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * attri_all_len * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	GLuint offset = 0;
	for (GLuint i = 0; i < attri_count; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attri_lens[i], GL_FLOAT, GL_FALSE, attri_all_len * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		offset += attri_lens[i];
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::Mesh(GLfloat * vertices, GLuint* indices, GLint vao_name, GLint vbo_name, GLint ebo_name, GLint vertex_count, GLint index_count, GLuint attri_count, GLint attri_all_len, GLuint* attri_lens)
{
	VAO_name = vao_name;
	VBO_name = vbo_name;
	EBO_nmae = ebo_name;

	glGenVertexArrays(vao_name, &VAO);
	glGenBuffers(vbo_name, &VBO);
	glGenBuffers(ebo_name, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * attri_all_len * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	GLuint offset = 0;
	for (GLuint i = 0; i < attri_count; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attri_lens[i], GL_FLOAT, GL_FALSE, attri_all_len * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		offset += attri_lens[i];
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(GLuint), (GLvoid*)indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(VAO_name, &VAO);
	glDeleteBuffers(VBO_name, &VBO);
	glDeleteBuffers(EBO_nmae, &EBO);
}

void Mesh::bind()
{
	glBindVertexArray(VAO);
}
