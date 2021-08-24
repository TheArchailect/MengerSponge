#include "FixedFunctionScene.h"
#include "../Application.h"

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
    glm::mat4 v = m_Camera->GetView();
    glMultMatrixf((GLfloat*)&v);
    Lighting();
    glPushMatrix();
    SetMaterial(*super::m_Mats.at(0));
    glm::mat4 m = m_VAO->GetTransform();
    glMultMatrixf((GLfloat*)&m);
    m_VAO->DrawLegacy();
    glPopMatrix();

    SetMaterial(*super::m_Mats.at(1));
    int s = 60;
    for (int x = -s; x < s; ++x)
    {
        for (int z = -s; z < s; ++z)
        {
            glPushMatrix();
            glTranslatef(x, 0, z);
            m_Grid->DrawLegacy();
            glPopMatrix();            
        }
    }
    glPopMatrix();
    Application::Get().GetWindow().Update();
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

void FixedFunctionScene::SetMaterial(const Material& m)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, m.Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m.Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m.Ks);
    glMaterialfv(GL_FRONT, GL_SHININESS, m.n);
}

void FixedFunctionScene::Lighting()
{
    GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glm::vec3 cp = m_Camera->GetPostition();
    GLfloat position[] = 
    { 
        cp.x, 
        cp.y, 
        cp.z, 1.0 
    };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
