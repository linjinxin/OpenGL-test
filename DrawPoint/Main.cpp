#include "Application.h"
#include <math.h>

void init()
{
	//创建 buffer 对象
	GLuint VBO;
	glGenBuffers(1, &VBO);
	//绑定 buffer 对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//定义数据
    GLfloat vertices[] = {
        0,0,0,
        0, 0.5f, 0,
        0.1f, 0.5f, 0,
        0.1f, 0, 0,
        0.2f, 0, 0,
        0.2f, 0.5f, 0,
        0.3f, 0.5f, 0,
        0.3f, 0, 0
    };
    //GLfloat vertices[114] = { 0,0,0 };
    //for (int i = 0; i <= 36; i++ )
    //{
    //    vertices[(i + 1) * 3] = cos(i * 10 * 3.14 / 180) * 0.8;
    //    vertices[(i + 1) * 3 + 1] = sin(i * 10 * 3.14 / 180) * 0.8;
    //    vertices[(i + 1) * 3 + 2] = 0;
    //}

	//填充 buffer 的值
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//开启顶点属性
	glEnableVertexAttribArray(0);
	//指定属性使用的 buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// 设置顶点大小
	glPointSize(15);
    glLineWidth(2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glDrawArrays(GL_POINTS, 0, 1);

    //glDrawArrays(GL_LINES, 0, 8);
    //glDrawArrays(GL_LINES_ADJACENCY, 0, 8);
    //glDrawArrays(GL_LINE_STRIP, 0, 8);
    //glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, 8);
    //glDrawArrays(GL_LINE_LOOP, 0, 8);

    //glDrawArrays(GL_TRIANGLES, 0, 8);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //glDrawArrays(GL_TRIANGLE_FAN, 0, 38);
    //glDrawArrays(GL_TRIANGLE_STRIP_ADJACENCY, 0, 38);
    glDrawArrays(GL_QUADS, 0, 4);
}

int main()
{
    Application app;
    sf::ContextSettings setting;
    setting.antialiasingLevel = 16;
    app.initWindow(400, 400, "Draw Point", sf::Style::Default, setting);
    app.initContext(init, display);

    app.start();
    while (true)
        if (!app.update())
            break;

    return 0;
}