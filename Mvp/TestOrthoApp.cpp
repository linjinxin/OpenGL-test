#include "TestOrthoApp.h"

TestOrthoApp::TestOrthoApp()
    :Application()
    ,_x1(-1),_x2(1),_y1(-1),_y2(1),_z1(-1),_z2(1)
{
}

TestOrthoApp::TestOrthoApp(int w, int h, const char* title)
    :Application(w, h, title)
    ,_x1(-1),_x2(1),_y1(-1),_y2(1),_z1(-1),_z2(1)
{
}

void TestOrthoApp::init()
{
    Application::init();

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    GLfloat vertices[] = {
        _x1, _y1, _z1,
        0.5,0,0,
        0,-1,-1,
        -0.5,0,0
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);

    glPointSize(5);
}

void TestOrthoApp::display()
{
    Application::display();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, 3);
}
