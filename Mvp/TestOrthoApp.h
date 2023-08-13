#pragma once
#include "Application.h"
class TestOrthoApp :
    public Application
{
public:
    TestOrthoApp();
    TestOrthoApp(int w, int h, const char* title);

private:
    void init();
    void display();

private:
    GLint _x1, _x2, _y1, _y2, _z1, _z2;
};

