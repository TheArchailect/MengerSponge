#define STB_IMAGE_IMPLEMENTATION
#include "Application.h"

EngineUtils* Application::m_Utils = nullptr;
Application* Application::s_Instance = nullptr;

Application::Application(unsigned int width, unsigned int height)
{
    std::cout << "Application base constructor" << std::endl;
    s_Instance = this;
    b_IsRunning = true;
    m_EventManager = new EventManager();
    m_Window = std::unique_ptr<Window>
    (
        Window::Create({ "Menger Sponge", width, height})
    );
    m_Input = new Input(static_cast<SDL_Window*>(m_Window->GetNativeWindow()));
    m_Utils = new EngineUtils();
    m_FullScreen = false; // TO DO
}

void Application::End(const Event<ApplicationEvent>& e)
{
    std::cout << "Application base deconstructor" << std::endl;
    //delete m_Input;
    //delete m_EventManager;
    //delete m_Utils;
}

void Application::Clear()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
