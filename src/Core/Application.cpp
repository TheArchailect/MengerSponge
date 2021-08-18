#define STB_IMAGE_IMPLEMENTATION
#include "Application.h"

EngineUtils* Application::m_Utils = nullptr;
Application* Application::s_Instance = nullptr;

Application::Application(uint32_t width, uint32_t height)
{
    s_Instance = this;
    m_FullScreen = false; // TO DO
    b_IsRunning = true;
    m_EventManager = new EventManager();
    m_Window = std::unique_ptr<Window>
    (
        Window::Create({ "Menger Sponge", width, height}, m_FullScreen)
    );
    m_Input = new Input
    (
        static_cast<SDL_Window*>(m_Window->GetNativeWindow())
    );
    m_Utils = new EngineUtils();
    BackFaceCulling = true;
    DepthTesting = true;
    Lighting = true;
}

void Application::Init()
{
    if (DepthTesting)
        glEnable(GL_DEPTH_TEST);
    if (BackFaceCulling)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::End(const Event<ApplicationEvent>& e)
{
    delete m_Input;
    delete m_Utils;
    delete m_EventManager;
}

void Application::Clear()
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
