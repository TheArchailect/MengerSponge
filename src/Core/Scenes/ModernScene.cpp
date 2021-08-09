#include "ModernScene.h"
#include "../Application.h"

ModernScene::ModernScene(int width, int height) : Scene(width, height)
{
	b_IsActive = false;
	RegisterCallbacks();
	m_Shader = new ShaderProgram
	(
		"src/Shaders/Default.vert",
		"src/Shaders/Default.frag"
	);
	glUseProgram(m_Shader->GetShaderProgramID());
	SetupMesh();
}

void ModernScene::Begin()
{
	super::b_IsActive = true;
}

void ModernScene::End()
{
	super::b_IsActive = false;
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
	if (super::b_IsActive)
	{
		super::Generate();
		SetupMesh();
	}
}

void ModernScene::SetupMesh()
{
	std::vector<Vertex> TempVertices;
	std::vector<unsigned int> Indices;

	for (Box* b : MengerSponge)
	{
		for (int i = 0; i < b->Vertices.size(); ++i)
		{
			TempVertices.push_back(Vertex(b->Vertices.at(i), b->Normals.at(i)));
		}		
	}
	Indices.push_back(1); // TO DO, Unused
	m_VAO = new Mesh(TempVertices, Indices);
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
		glm::mat4(1), 
		m_Camera->GetView(), 
		m_Camera->GetProjection(), 
		*m_Camera
	);
}