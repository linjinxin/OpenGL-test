#include "Application.h"
#include <iostream>

Application::Application(int w, int h, const char* title, int style, sf::ContextSettings setting)
{
    _isRunning = false;
    initWindow(w, h, title, style, setting);
}

void Application::initWindow(int w, int h, const char* title /* = "Window" */, int style /* = sf::Style::Default */, sf::ContextSettings setting)
{
    _window.create(sf::VideoMode(w, h), title, style, setting);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);
}

void Application::initContext(FUNC_V func1, FUNC_V func2)
{
    glewExperimental = true;
    if (GLEW_OK != glewInit())
    {
        std::cerr << "Init glew fail!" << std::endl;
        return;
    }

    _initFunc = func1;
    _displayFunc = func2;

    glViewport(0, 0, _window.getSize().x, _window.getSize().y);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Application::start()
{
    _isRunning = true;
    if (_initFunc)
        _initFunc();
}

bool Application::update()
{
    if (!_window.isOpen())
        return false;

    sf::Event evt;
    while (_window.pollEvent(evt))
    {
        sf::Event::EventType type = evt.type;
        switch (type)
        {
        case sf::Event::Closed:
            _window.close();
            break;
        case sf::Event::Resized:
            onResize(evt.size.width, evt.size.height);
            break;
        case sf::Event::LostFocus:
            break;
        case sf::Event::GainedFocus:
            break;
        case sf::Event::TextEntered:
            break;
        case sf::Event::KeyPressed:
            break;
        case sf::Event::KeyReleased:
            break;
        case sf::Event::MouseWheelMoved:
            break;
        case sf::Event::MouseWheelScrolled:
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        case sf::Event::MouseEntered:
            break;
        case sf::Event::MouseLeft:
            break;
        case sf::Event::JoystickButtonPressed:
            break;
        case sf::Event::JoystickButtonReleased:
            break;
        case sf::Event::JoystickMoved:
            break;
        case sf::Event::JoystickConnected:
            break;
        case sf::Event::JoystickDisconnected:
            break;
        case sf::Event::TouchBegan:
            break;
        case sf::Event::TouchMoved:
            break;
        case sf::Event::TouchEnded:
            break;
        case sf::Event::SensorChanged:
            break;
        default:
            break;
        }
    }

    if (_displayFunc)
        _displayFunc();

    _window.display();

    return true;
}

void Application::setInitFunc(FUNC_V func)
{
    this->_initFunc = func;
}

void Application::setDisplayFunc(FUNC_V func)
{
    this->_displayFunc = func;
}

void Application::onResize(unsigned int w, unsigned int h)
{
    glViewport(0, 0, w, h);

    if (_displayFunc)
        _displayFunc();
    _window.display();
}

