#include "InstancedGeometry.h"
#include "../Application.h"

InstancedGeometry::InstancedGeometry(int width, int height) : Scene(width, height)
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

void InstancedGeometry::Begin()
{
	super::b_IsActive = true;
	super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
	
	// this is gross
	m_Camera->m_Position.z = 80;
	m_Camera->m_Position.y = 5;
	m_Camera->Pitch = 0;
	m_Camera->Yaw = -90;
}

void InstancedGeometry::End()
{
	super::b_IsActive = false;
	super::IndexOffset = 0;
	m_Sponge.clear();
	m_Indices.clear();
	glUseProgram(0);
	delete m_VAO;
}

void InstancedGeometry::Render()
{
	glUseProgram(m_Shader->GetShaderProgramID());

	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(25, 25, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(0, 25, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(-25, 25, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(-25, 0, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(0, 0, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(25, 0, 0)));
	m_VAO->Draw(GL_TRIANGLES);

	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(-25, -25, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(0, -25, 0)));
	m_VAO->Draw(GL_TRIANGLES);
	Update(glm::translate(m_VAO->GetTransform(), glm::vec3(25, -25, 0)));
	m_VAO->Draw(GL_TRIANGLES);

	Application::Get().GetWindow().Update();
}

void InstancedGeometry::GeometryGenerate(const Event<ApplicationEvent>& e)
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

void InstancedGeometry::RegisterCallbacks()
{
	EventManager::Get().ApplicationDispatcher.Subscribe
	(
		ApplicationEvent::GENERATE,
		std::bind
		(
			&InstancedGeometry::GeometryGenerate,
			this,
			std::placeholders::_1
		)
	);
}

// TODO update shader class to be updated more specficialy per app
void InstancedGeometry::Update(glm::mat4 ModelTransform)
{
	UpdateShader
	(
		m_Shader->GetShaderProgramID(),
		ModelTransform,
		m_Camera->GetView(),
		m_Camera->GetProjection(),
		*m_Camera,
		super::m_Mats,
		super::m_Lights
	);
}