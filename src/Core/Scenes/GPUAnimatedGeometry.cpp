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
	std::vector<Vertex> v;
	std::vector<uint32_t> i;

	v.push_back(Vertex(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
	v.push_back(Vertex(glm::vec3(10, 0, 0), glm::vec3(0, 0, 0)));
	v.push_back(Vertex(glm::vec3(0, 10, 0), glm::vec3(0, 0, 0)));
	v.push_back(Vertex(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0)));
	v.push_back(Vertex(glm::vec3(-10, 0, 0), glm::vec3(0, 0, 0)));
	v.push_back(Vertex(glm::vec3(0, -10, 0), glm::vec3(0, 0, 0)));
	v.push_back(Vertex(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0)));

	for (int idx = 0; idx < 7; ++idx) i.push_back(idx);
	m_Axis = new Mesh(v, i);
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
	glPointSize(8);
	m_Axis->Draw(GL_LINES);
	//m_Grid->Draw(GL_TRIANGLES);
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
		float radius = 10.0f;
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
	glm::vec3 fp(10, 10, 10);
	glm::vec3 np = glm::normalize(point);
	float MaxOffset = glm::distance(fp, origin) - radius;
	glm::vec3 cp = fp / 5.0f;
	float U = Map(glm::distance(point, origin), glm::distance(cp, origin), glm::distance(fp, origin), 0.5, 1.0f);
	return glm::mix(point * 0.8f, point * 0.23f, EaseOut(U));
}

float GPUAnimatedGeometry::Map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

#ifndef PI
#define PI 3.14159265359
#endif
float GPUAnimatedGeometry::EaseOut(float t)
{
	//return 1 - cos((t * PI) / 2);
	//std::cout << t << std::endl;
	if (t > 0.98) return 0.98;
	if (t < 0.4) return 0.4;
	return t;
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
