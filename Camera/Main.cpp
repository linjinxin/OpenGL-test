#include "MyApplication.h"

int main(int argc, void** argv)
{
    MyApplication app;
    app.initWindow(800, 800, "Camera", sf::Style::Default);
    return 0;
}