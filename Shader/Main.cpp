#include "Application.h"
#include <iostream>
#include <fstream>
#include <sstream>


GLuint shaderProgram;

void init()
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLfloat vertices[][6] = {
        { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.5f, -0.5f, 0.0f , 0.0f, 1.0f, 0.0f },
        { 0.0f,  0.5f, 0.0f , 0.0f, 0.0f, 1.0f }
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	std::ifstream vertexFile;
	std::stringstream vertexBuffer;
	std::string vertexString;
	const GLchar* vertexSource;
	vertexFile.open("vertex.vs", std::ios::in);
	vertexBuffer << vertexFile.rdbuf();
	vertexFile.close();
	vertexString = vertexBuffer.str();
	vertexSource = vertexString.c_str();

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, info);
		std::cout << info << std::endl;
	}

	std::ifstream fragmentFile;
	std::stringstream fragmentBuffer;
	std::string fragmentString;
	const GLchar* fragmentSource;
	fragmentFile.open("fragment.fs", std::ios::in);
	fragmentBuffer << fragmentFile.rdbuf();
	fragmentString = fragmentBuffer.str();
	fragmentSource = fragmentString.c_str();

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, info);
		std::cout << info << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, info);
		std::cout << info << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

int main()
{
    Application app(400, 400, "Shader");
    app.initContext(init, display);

    app.start();
    while (true)
        if (!app.update())
            break;

    return 0;
}