#define STB_IMAGE_IMPLEMENTATION
#include "Application.h"

EngineUtils* Application::m_Utils = nullptr;
Application* Application::s_Instance = nullptr;

Application::Application(unsigned int width, unsigned int height)
{
    s_Instance = this;
    m_FullScreen = false; // TO DO
    b_IsRunning = true;
    m_EventManager = new EventManager();
    m_Window = std::unique_ptr<Window>
    (
        Window::Create({ "Menger Sponge", width, height}, m_FullScreen)
    );
    m_Input = new Input(static_cast<SDL_Window*>(m_Window->GetNativeWindow()));
    m_Utils = new EngineUtils();
}

void Application::End(const Event<ApplicationEvent>& e)
{
    std::cout << "Application base deconstructor" << std::endl;
    delete m_Input;
    //delete m_EventManager;
    delete m_Utils;
}

void Application::Clear()
{
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_LIGHTING); // ?
    glEnable(GL_DEPTH_TEST);
    //
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// move this in fixed function
void Application::SetMaterial(const Material& m)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, m.n);
}
