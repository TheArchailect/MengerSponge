#include "FixedFunctionScene.h"
#include "../Application.h"

// lighting
GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_position[] = { 1.0, 200.0, -100.0, 0.0 };

FixedFunctionScene::FixedFunctionScene(int width, int height) : Scene(width, height)
{
    std::cout << "Fixed Function Constructor" << std::endl;
    RegisterCallbacks();
}

void FixedFunctionScene::Begin()
{
    super::b_IsActive = true;
}

void FixedFunctionScene::End()
{
    super::b_IsActive = false;
}

void FixedFunctionScene::Render()
{
    Update();
    glPushMatrix(); 
    glm::mat4 v = m_Camera->GetView();
    glMultMatrixf((GLfloat*)&v);
    for (Box* b : MengerSponge)
    {
        b->Draw();
    }
    Application::Get().GetWindow().Update();
    // lighting start
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // lighting end
    glPopMatrix();
}

void FixedFunctionScene::GeometryGenerate(const Event<ApplicationEvent>& e)
{
    if (super::b_IsActive)
    super::Generate();
}

void FixedFunctionScene::RegisterCallbacks()
{
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::GENERATE,
        std::bind
        (
            &FixedFunctionScene::GeometryGenerate,
            this,
            std::placeholders::_1
        )
    );
}

void FixedFunctionScene::Update()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 p = m_Camera->GetProjection();
    glMultMatrixf((GLfloat*)&p);
    glMatrixMode(GL_MODELVIEW);
}
