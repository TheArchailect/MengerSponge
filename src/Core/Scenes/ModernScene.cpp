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
	//SetupMesh(glm::vec3(0, 0, 0), 15, IndexOffset);
	//m_VAO = new Mesh(m_Sponge, m_Indices);
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
	glPointSize(8);
	m_VAO->Draw(GL_TRIANGLES);
	Application::Get().GetWindow().Update();
}

void ModernScene::GeometryGenerate(const Event<ApplicationEvent>& e)
{
	if (super::b_IsActive)
	{
		//std::cout << "Generate Geo" << std::endl;
		super::CurrentSubdivision++;
		super::IndexOffset = 0;
		m_Sponge.clear();
		m_Indices.clear();
		float size = 15;
		super::Subdivide(glm::vec3(0, 0, 0), size, CurrentSubdivision);
		//SetupMesh(glm::vec3(0, 0, 0), size, CurrentSubdivision);
		m_VAO = new Mesh(m_Sponge, m_Indices);
	}
}

void ModernScene::SetupMesh(glm::vec3 Position, float s, int subd)
{
	//for (int x = -1; x < 2; ++x)
	//{
	//	for (int y = -1; y < 2; ++y)
	//	{
	//		for (int z = -1; z < 2; ++z)
	//		{
	//			int check = abs(x) + abs(y) + abs(z);
	//			if (check > 1)
	//			{
	//				float Size = (s / 3);
	//				glm::vec3 Origin = glm::vec3
	//				(
	//					Position.x + x * Size,
	//					Position.y + y * Size,
	//					Position.z + z * Size
	//				);
	//				if (subd > 0)SetupMesh(Origin, Size, subd - 1);
	//				else
	//				{
	//					Subdivide(Origin, Size / 2);
	//					IndexOffset++;
	//				}
	//			}
	//		}
	//	}
	//}
	
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

//glm::vec3 ModernScene::CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
//{
//	glm::vec3 A = p2 - p1;
//	glm::vec3 B = p3 - p1;
//	return glm::normalize(glm::cross(A, B));
//}