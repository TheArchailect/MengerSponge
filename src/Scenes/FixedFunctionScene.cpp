#include "FixedFunctionScene.h"
#include "Application/Application.h"

FixedFunctionScene::FixedFunctionScene(int width, int height) : Scene(width, height)
{
    RegisterCallbacks();
}

void FixedFunctionScene::Begin()
{   
    Update();
    super::b_IsActive = true;
    super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
    m_VAO = new Mesh(m_Sponge, m_Indices);
    m_Camera->Reset(glm::vec3(0, 5, 40), -90, 0);
}

void FixedFunctionScene::End()
{
    super::b_IsActive = false;
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    super::IndexOffset = 0;
    m_Sponge.clear();
    m_Indices.clear();
    delete m_VAO;
}

void FixedFunctionScene::Render()
{   
    glPushMatrix();
    {
        glm::mat4 v = m_Camera->GetView();
        glMultMatrixf((GLfloat*)&v);
        glPushMatrix();
        glm::mat4 m = m_VAO->GetTransform();
        glMultMatrixf((GLfloat*)&m);
        Lighting();
        m_VAO->DrawLegacy(super::m_Mats);
        glPopMatrix();
    }
    glPopMatrix();
    Application::Get().GetWindow().Update();
}

int FixedFunctionScene::TriangleCount()
{
    return m_VAO->GetElementCount() / 3;
}

void FixedFunctionScene::GeometryGenerate(const Event<ApplicationEvent>& e)
{
    if (super::b_IsActive)
    {
        super::CurrentSubdivision += e.division;
        super::IndexOffset = 0;
        m_Sponge.clear();
        m_Indices.clear();
        super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
        m_VAO = new Mesh(m_Sponge, m_Indices);
    }
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
    glLoadMatrixf(glm::value_ptr(p));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void FixedFunctionScene::Lighting()
{
    glPushMatrix();
    for (int i = 0; i < 9; ++i) glDisable(GL_LIGHT0 + i);
    if (Application::Get().b_Lighting && super::m_LightCount > 0)
    {
        {
            glEnable(GL_LIGHTING);
            GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
            GLfloat local_view[] = { 1.0 };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
            glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
            for (int i = 0; i < super::m_LightCount && i < 9 && i < m_Lights.size(); ++i)
            {
                glLightfv(GL_LIGHT0 + i, GL_AMBIENT, &m_Lights.at(i)->Ambient[0]);
                glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, &m_Lights.at(i)->Diffuse[0]);
                glLightfv(GL_LIGHT0 + i, GL_POSITION, &m_Lights.at(i)->Position[0]);
                glEnable(GL_LIGHT0 + i);
            }
        }
    }
    else glDisable(GL_LIGHTING);
    glPopMatrix();
}
