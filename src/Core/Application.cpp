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
    b_BackFaceCulling = true;
    b_DepthTesting = true;
    b_Lighting = true;
}

void Application::Init()
{
    if (b_DepthTesting)
        glEnable(GL_DEPTH_TEST);
    if (b_BackFaceCulling)
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

void Application::RegisterCallbacks()
{
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::TOGGLE_BACKFACECULLING,
        std::bind
        (
            &Application::ToggleBackfaceCulling,
            this,
            std::placeholders::_1
        )
    );
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::TOGGLE_LIGHTING,
        std::bind
        (
            &Application::ToggleLighting,
            this,
            std::placeholders::_1
        )
    );
}

void Application::ToggleLighting(const Event<ApplicationEvent>& e)
{
    if (b_Lighting)
    {
        b_Lighting = false;
    }
}

void Application::ToggleBackfaceCulling(const Event<ApplicationEvent>& e)
{
    if (b_BackFaceCulling)
    {
        b_BackFaceCulling = false;
    }
}

void Application::Clear()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
