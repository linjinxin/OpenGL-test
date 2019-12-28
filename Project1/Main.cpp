#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Application app;
Mesh* mesh;
Shader* shader;
Texture* texture;

//摄像机
glm::vec3 cameraPos = glm::vec3(0, 0, 4);
glm::vec3 cameraDirection = glm::vec3(0, 0, -1);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);

//摄像机缩放
GLfloat fov = 45.0f;

//立方体变换
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

void init();
void display();

int main()
{
    sf::ContextSettings setting;
    setting.antialiasingLevel = 16;
    setting.depthBits = 24;
    app.initWindow(400, 400, "First Window", sf::Style::Default, setting);
    app.initContext(init, display);

    app.start();

    while (true)
    {
        if (!app.update())
            break;
    }

    return 0;
}

void init()
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	GLuint attri_len[] = { 3,2 };

	mesh = new Mesh(vertices, 1, 1, 36, 2, 5, attri_len);
    GLchar vert[16] = "res/vert.vs";
    GLchar frag[16] = "res/frag.fs";
    shader = new Shader(vert, frag);
	texture = new Texture("res/face.png", 1);

	mesh->bind();
	GLint location = glGetUniformLocation(shader->getProgram(), "Texture");
	texture->bind(location, 0);
	shader->use();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//视图矩阵
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
	GLint location = glGetUniformLocation(shader->getProgram(), "view");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));

	//投影矩阵
    auto size = app.getWindow().getSize();
	glm::mat4 projection = glm::perspective(glm::radians(fov), 1.0f * size.x / size.y, 1.0f, 100.0f);
	location = glGetUniformLocation(shader->getProgram(), "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

	for (int i = 0; i < 10; i++)
	{
		//模型矩阵
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, 2.0f * i, glm::vec3(1.0f, 0.3f, 0.5f));
		location = glGetUniformLocation(shader->getProgram(), "model");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

