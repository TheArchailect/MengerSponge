#include "Scene.h"
#include "Application.h"
Scene::Scene(int width, int height)
{
    std::cout << "Scene base constructor" << std::endl;
    RegisterCallbacks();
    m_Camera = new Camera(width, height);
	Box* b = new Box(glm::vec3(0, 0, 0), 10);
	MengerSponge = b->Generate();
}

void Scene::Render()
{
    Update();
    glPushMatrix();
    glm::mat4 v = m_Camera->GetView();
    glMultMatrixf((GLfloat*)&v);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (Box* b : MengerSponge)
    {
        b->Draw();
    }
    Application::Get().GetWindow().Update();
    glPopMatrix();
}

void Scene::Generate(const Event<ApplicationEvent>& e)
{
    std::vector<Box*> generated;
    for (Box* b : MengerSponge)
    {
        std::vector<Box*> temp = b->Generate();
        for (Box* tb : temp)
        {
            generated.push_back(tb);
        }
    }
    MengerSponge = generated;
}

void Scene::RegisterCallbacks()
{
    EventManager::Get().ApplicationDispatcher.Subscribe
    (
        ApplicationEvent::GENERATE,
        std::bind
        (
            &Scene::Generate,
            this,
            std::placeholders::_1
        )
    );
}

void Scene::Update()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 p = m_Camera->GetProjection();
    glMultMatrixf((GLfloat*)&p);
    glMatrixMode(GL_MODELVIEW);
}
