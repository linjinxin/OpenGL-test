#include "Shader.h"

using namespace std;

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	//������ɫ��
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//��ȡ��ɫ���ļ�
	ifstream vertexFile, fragmentFile;
	stringstream vertexBuffer, fragmentBuffer;
	string vertexString, fragmentString;
	const GLchar* vertexSource;
	const GLchar* fragmentSource;

	vertexFile.open(vertexPath, ios::in);
	vertexBuffer << vertexFile.rdbuf();
	vertexString = vertexBuffer.str();
	vertexSource = vertexString.c_str();

	fragmentFile.open(fragmentPath, ios::in);
	fragmentBuffer << fragmentFile.rdbuf();
	fragmentString = fragmentBuffer.str();
	fragmentSource = fragmentString.c_str();

	//������ɫ��
	GLint status;
	GLchar errInfo[512];
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errInfo);
		cout << errInfo << endl;
		//return Shader::COMPILE_ERROR;
	}

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errInfo);
		cout << errInfo << endl;
		//return Shader::COMPILE_ERROR;
	}

	//������ɫ������
	this->glProgram = glCreateProgram();

	//������ɫ��
	glAttachShader(glProgram, vertexShader);
	glAttachShader(glProgram, fragmentShader);
	glLinkProgram(glProgram);
	glGetProgramiv(glProgram, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(glProgram, 512, NULL, errInfo);
		cout << errInfo << endl;
		//return Shader::LINK_ERROR;
	}

	//ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//return Shader::SUCCESS;
}

Shader::~Shader()
{
	glDeleteProgram(glProgram);
}

void Shader::use()
{
	glUseProgram(glProgram);
}

GLuint Shader::getProgram()
{
	return this->glProgram;
}
