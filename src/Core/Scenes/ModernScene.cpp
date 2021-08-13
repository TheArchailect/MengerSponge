#include "ModernScene.h"
#include "../Application.h"

ModernScene::ModernScene(int width, int height) : Scene(width, height)
{
	b_IsActive = false;
	RegisterCallbacks();
	m_Shader = new ShaderProgram
	(
		"src/Shaders/Default.vert",
		"src/Shaders/Default.geom",
		"src/Shaders/Default.frag"
	);
	glUseProgram(m_Shader->GetShaderProgramID());
}

void ModernScene::Begin()
{
	super::b_IsActive = true;
	super::Subdivide(glm::vec3(0, 0, 0), 10, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
}

void ModernScene::End()
{
	super::b_IsActive = false;
	super::IndexOffset = 0;
	m_Sponge.clear();
	m_Indices.clear();
	glUseProgram(0);
	delete m_VAO;
}

void ModernScene::Render()
{
	glUseProgram(m_Shader->GetShaderProgramID());
	Update();
	m_VAO->Draw(GL_TRIANGLES);
	Application::Get().GetWindow().Update();
}

void ModernScene::GeometryGenerate(const Event<ApplicationEvent>& e)
{
	std::cout << "Generate Geo: MM" << std::endl;
	if (super::b_IsActive)
	{
		std::cout << "inner block" << std::endl;
		super::CurrentSubdivision += e.division;
		super::IndexOffset = 0;
		m_Sponge.clear();
		m_Indices.clear();
		float size = 15;
		super::Subdivide(glm::vec3(0, 0, 0), size, CurrentSubdivision);
		m_VAO = new Mesh(m_Sponge, m_Indices);
	}
}

void ModernScene::RegisterCallbacks()
{
	EventManager::Get().ApplicationDispatcher.Subscribe
	(
		ApplicationEvent::GENERATE,
		std::bind
		(
			&ModernScene::GeometryGenerate,
			this,
			std::placeholders::_1
		)
	);
}

void ModernScene::Update()
{
	UpdateShader
	(
		m_Shader->GetShaderProgramID(), 
		m_VAO->GetTransform(), 
		m_Camera->GetView(), 
		m_Camera->GetProjection(), 
		*m_Camera
	);
}

void ModernScene::SetMaterial(const Material& m)
{

}