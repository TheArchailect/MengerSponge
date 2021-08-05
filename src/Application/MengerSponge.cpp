#include "MengerSponge.h"

MengerSponge::MengerSponge(unsigned int width, unsigned int height) : Application(width, height)
{
    std::cout << "Application sub-class constructor" << std::endl;
    RegisterCallbacks();
    Init();
    m_Scene = new Scene(width, height);
}

void MengerSponge::Tick()
{
    super::GetUtils().DeltaTime();
    super::GetUtils().FrameRate();
    CameraUpdate e;
    m_EventManager->CameraDispatcher.Post(e);
    
    super::Clear();
    RenderOverlay();
    RenderFrame();
    super::m_Input->Update();
}

void MengerSponge::RenderOverlay()
{
    char str[30];
    gltBeginDraw();
    gltColor(1, 0, 0, 0.7);
    sprintf_s(str, "FPS: %.2f", Application::GetUtils().m_FPS);
    gltSetText(fps, str);
    gltDrawText2DAligned(fps, 0.0f, Application::GetWindow().m_Data.Height, 1.0f, GLT_LEFT, GLT_BOTTOM);
    gltEndDraw();
}

// application subclass subscription to app events
void MengerSponge::RegisterCallbacks()
{
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::APPLICATION_END,
        std::bind
        (
            &MengerSponge::End,
            this,
            std::placeholders::_1
        )
    );
}

void MengerSponge::RenderFrame()
{
    m_Scene->Render();
}

bool MengerSponge::Init()
{
    // text
    int glt = gltInit();
    fps = gltCreateText();
    // lighting etc
    GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 100.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    return true; // do some checks here
}

void MengerSponge::Run()
{
    std::cout << "Application subclass run" << std::endl;
    while (super::b_IsRunning)
    {
        Tick(); // maybe replace with a tick event creation?
    }
}

void MengerSponge::End(const Event<ApplicationEvent>& e)
{
    std::cout << "Application subclass deconstructor" << std::endl;
    super::b_IsRunning = false;
    gltDeleteText(fps);
    gltTerminate();
    super::End(e);
}