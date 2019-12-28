#pragma once
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <functional>

typedef std::function<void()> FUNC_V;

class Application
{
public:
    Application(int w, int h, const char* title = "Window", int style = sf::Style::Default, sf::ContextSettings setting = sf::ContextSettings());
    Application() :_isRunning(false) {}
    ~Application() {}
    void initWindow(int w, int h, const char* title = "Window", int style = sf::Style::Default, sf::ContextSettings setting = sf::ContextSettings());
    void initContext(FUNC_V func1, FUNC_V func2);

    void setInitFunc(FUNC_V func);
    void setDisplayFunc(FUNC_V func);

    void start();
    bool update();
    void onResize(unsigned int w, unsigned int h);

    sf::Window& getWindow() { return _window; }

private:
    sf::Window _window;
    std::function<void()> _initFunc;
    std::function<void()> _displayFunc;

    bool _isRunning;
};

