#include "CPUAnimatedGeometry.h"
#include "../Application.h"

CPUAnimatedGeometry::CPUAnimatedGeometry(int width, int height) : Scene(width, height)
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

void CPUAnimatedGeometry::Begin()
{
	super::b_IsActive = true;
	super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
	// TODO generate a keyframe to pass to the gpu
}

void CPUAnimatedGeometry::End()
{
	super::b_IsActive = false;
	super::IndexOffset = 0;
	m_Sponge.clear();
	m_Indices.clear();
	glUseProgram(0);
	delete m_VAO;
}

void CPUAnimatedGeometry::Render()
{
	glUseProgram(m_Shader->GetShaderProgramID());
	Update(m_VAO->GetTransform());
	float AnimationTime = Map(cos(SDL_GetTicks() / 1000), -1, 1, 0, 1);
	std::vector<Vertex> mesh;
	for (int i = 0; i < m_Sponge.size(); ++i)
	{
		mesh.push_back
		(
			Vertex
			(
				glm::mix(m_Sponge.at(i).Position, m_Sponge.at(i).Normal, AnimationTime), 
				glm::vec3(0, 0, 0)
			)
		);
	}
	m_VAO = new Mesh(mesh, m_Indices);
	m_VAO->Draw(GL_TRIANGLES);
	Application::Get().GetWindow().Update();
}

void CPUAnimatedGeometry::GeometryGenerate(const Event<ApplicationEvent>& e)
{
	if (super::b_IsActive)
	{
		super::CurrentSubdivision += e.division;
		super::IndexOffset = 0;
		m_Sponge.clear();
		m_Indices.clear();
		super::Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
		// sphere cast verts and pack them into the normal attribute
		float radius = 10.0f;
		for (int i = 0; i < m_Sponge.size(); ++i)
		{
			m_Sponge.at(i).Normal = SphereCast(glm::vec3(0, 0, 0), m_Sponge.at(i).Position, radius);
		}
		// end
		m_VAO = new Mesh(m_Sponge, m_Indices);
	}
}

glm::vec3 CPUAnimatedGeometry::SphereCast(glm::vec3 origin, glm::vec3 point, float radius)
{
	glm::vec3 fp(10, 10, 10);
	glm::vec3 np = glm::normalize(point);
	float MaxOffset = glm::distance(fp, origin) - radius;

	float U = Map(glm::distance(point, origin), 5.0f, glm::distance(fp, origin), 0.0, 1.0f);
	return glm::mix(point * 0.7f, point * 0.4f, U);
}

float CPUAnimatedGeometry::Map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

#ifndef PI
#define PI 3.14159265359
#endif
float CPUAnimatedGeometry::EaseOut(float t)
{
	return t;
}

void CPUAnimatedGeometry::RegisterCallbacks()
{
	EventManager::Get().ApplicationDispatcher.Subscribe
	(
		ApplicationEvent::GENERATE,
		std::bind
		(
			&CPUAnimatedGeometry::GeometryGenerate,
			this,
			std::placeholders::_1
		)
	);
}

// TODO update shader class to be updated more specficialy per app
void CPUAnimatedGeometry::Update(glm::mat4 ModelTransform)
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
