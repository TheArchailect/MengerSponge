#include "GPUAnimatedGeometry.h"
#include "../Application.h"

GPUAnimatedGeometry::GPUAnimatedGeometry(int width, int height) : Scene(width, height)
{
	b_IsActive = false;
	RegisterCallbacks();
	m_Shader = new ShaderProgram
	(
		"src/Shaders/GPUAnimatedGeometry.vert",
		"src/Shaders/Default.geom",
		"src/Shaders/Default.frag"
	);
	glUseProgram(m_Shader->GetShaderProgramID());
}

void GPUAnimatedGeometry::Begin()
{
	super::b_IsActive = true;
	super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
	// TODO generate a keyframe to pass to the gpu
}

void GPUAnimatedGeometry::End()
{
	super::b_IsActive = false;
	super::IndexOffset = 0;
	m_Sponge.clear();
	m_Indices.clear();
	glUseProgram(0);
	delete m_VAO;
}

void GPUAnimatedGeometry::Render()
{
	glUseProgram(m_Shader->GetShaderProgramID());
	Update();
	m_VAO->Draw(GL_TRIANGLES);
	Application::Get().GetWindow().Update();
}

void GPUAnimatedGeometry::GeometryGenerate(const Event<ApplicationEvent>& e)
{
	if (super::b_IsActive)
	{
		super::CurrentSubdivision += e.division;
		super::IndexOffset = 0;
		m_Sponge.clear();
		m_Indices.clear();
		super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
		// sphere cast verts and pack them into the normal attribute
		float radius = 25.0f;
		for (int i = 0; i < m_Sponge.size(); ++i)
		{
			m_Sponge.at(i).Normal = SphereCast(glm::vec3(0, 0, 0) , m_Sponge.at(i).Position, radius);
		}
		// end
		m_VAO = new Mesh(m_Sponge, m_Indices);
	}
}

glm::vec3 GPUAnimatedGeometry::SphereCast(glm::vec3 origin, glm::vec3 point, float radius)
{
	glm::vec3 ndir = glm::normalize(point - origin);
	return ndir * radius;
}

void GPUAnimatedGeometry::RegisterCallbacks()
{
	EventManager::Get().ApplicationDispatcher.Subscribe
	(
		ApplicationEvent::GENERATE,
		std::bind
		(
			&GPUAnimatedGeometry::GeometryGenerate,
			this,
			std::placeholders::_1
		)
	);
}

// TODO update shader class to be updated more specficialy per app
void GPUAnimatedGeometry::Update()
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

// TODO
void GPUAnimatedGeometry::SetMaterial(const Material& m)
{

}
