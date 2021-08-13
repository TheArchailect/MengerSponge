#include "FixedFunctionScene.h"
#include "../Application.h"

FixedFunctionScene::FixedFunctionScene(int width, int height) : Scene(width, height)
{
    RegisterCallbacks();
}

void FixedFunctionScene::Begin()
{   
    super::b_IsActive = true;
    super::Subdivide(glm::vec3(0, 0, 0), 10, CurrentSubdivision);
    m_VAO = new Mesh(m_Sponge, m_Indices);
    glEnable(GL_LIGHTING);
}

void FixedFunctionScene::End()
{
    super::b_IsActive = false;
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    //m_Sponge.clear();
    //m_Indices.clear();
    delete m_VAO;

}

void FixedFunctionScene::Render()
{
    SetMaterial(*CyanPlastic);
    Update();
    glPushMatrix(); 
    glm::mat4 v = m_Camera->GetView();
    glMultMatrixf((GLfloat*)&v);
    m_VAO->DrawLegacy();
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
    std::cout << "Geo Generate: IM" << std::endl;
    if (super::b_IsActive)
    {
        std::cout << "inner block" << std::endl;
        super::CurrentSubdivision += e.division;
        super::IndexOffset = 0; // TO DO unused in IM
        m_Sponge.clear();
        m_Indices.clear();
        super::Subdivide(glm::vec3(0, 0, 0), 15, CurrentSubdivision);
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
    glMultMatrixf((GLfloat*)&p);
    glMatrixMode(GL_MODELVIEW);
}

void FixedFunctionScene::SetMaterial(const Material& m)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, m.n);
}
