#pragma once
#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <functional>

typedef std::function<void()> FUNC_V;

class Application
{
public:
    Application(int w, int h, const char* title, int style, sf::ContextSettings setting);
    Application(int w, int h, const char* title);
    Application();
    ~Application();

    void initWindow(int w, int h, const char* title = "Window", int style = sf::Style::Default, sf::ContextSettings setting = sf::ContextSettings());
    void initContext();
    void initContext(FUNC_V, FUNC_V);

    void setInitFunc(FUNC_V func);
    void setDisplayFunc(FUNC_V func);

    virtual void start();
    virtual bool update();

    sf::Window* getWindow() const { return _window; }

protected:
    virtual void init();
    virtual void display();
    virtual void onResize(unsigned int w, unsigned int h);

protected:
    sf::Window *_window;
    bool _isInitGL;

    std::function<void()> _initFunc;
    std::function<void()> _displayFunc;

    bool _isRunning;
};

