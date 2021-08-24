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
	m_Camera->Reset(glm::vec3(0, 5, 45), -90, 0);
	Generate e(0);
	EventManager::Get().ApplicationDispatcher.Post(e);
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
	Update();
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
		float radius = 10.0f;
		for (int i = 0; i < m_Sponge.size(); ++i)
		{
			m_Sponge.at(i).Normal = SphereCast(glm::vec3(0, 0, 0), m_Sponge.at(i).Position, radius);
		}
		m_VAO = new Mesh(m_Sponge, m_Indices);
	}
}

glm::vec3 CPUAnimatedGeometry::SphereCast(glm::vec3 origin, glm::vec3 point, float radius)
{
	float intersection = 0;
	float size = 10.0f;
	if (abs(point.x) >= abs(point.y) && abs(point.x) >= abs(point.z))
	{
		intersection = size / point.x;
	}
	if (abs(point.y) >= abs(point.x) && abs(point.y) >= abs(point.z))
	{
		intersection = size / point.y;
	}
	if (abs(point.z) >= abs(point.y) && abs(point.z) >= abs(point.x))
	{
		intersection = size / point.z;
	}

	glm::vec3 P = point * intersection;
	float mdist = glm::distance(origin, P);
	float Percentage = glm::distance(origin, point) / mdist;
	glm::vec3 R(radius, 0, 0);
	float dif = glm::length(R * Percentage) / glm::length(point);
	if (dif < 1.0f)
	{
		return P = point * dif;
	}
	return point;
}

float CPUAnimatedGeometry::Map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
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

void CPUAnimatedGeometry::Update()
{
	// matricies
	SetMat4(m_Shader->GetShaderProgramID(), "Model", m_VAO->GetTransform());
	SetMat4(m_Shader->GetShaderProgramID(), "View", m_Camera->GetView());
	SetMat4(m_Shader->GetShaderProgramID(), "Projection", m_Camera->GetProjection());
	// camera
	SetVec3(m_Shader->GetShaderProgramID(), "Camera", m_Camera->GetPostition());
	// lighting directional
	m_DirectionLight->Lp = m_Camera->GetForward();
	SetVec3(m_Shader->GetShaderProgramID(), "u_Light.Direction", m_DirectionLight->Lp);
	SetVec3(m_Shader->GetShaderProgramID(), "u_Light.Ambient", m_DirectionLight->La);
	SetVec3(m_Shader->GetShaderProgramID(), "u_Light.Diffuse", m_DirectionLight->Ld);
	SetVec3(m_Shader->GetShaderProgramID(), "u_Light.Specular", m_DirectionLight->Ls);
	// lighting point
	SetInt(m_Shader->GetShaderProgramID(), "LightCount", m_LightCount);
	for (int i = 0; i < m_LightCount; ++i)
	{
		std::string idx = std::to_string(i);
		SetVec3(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Position").c_str(), super::m_Lights.at(i)->Position);
		SetVec3(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Ambient").c_str(), super::m_Lights.at(i)->Ambient);
		SetVec3(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Diffuse").c_str(), super::m_Lights.at(i)->Diffuse);
		SetVec3(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Specular").c_str(), super::m_Lights.at(i)->Specular);
		SetFloat(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Constant").c_str(), super::m_Lights.at(i)->Constant);
		SetFloat(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Linear").c_str(), super::m_Lights.at(i)->Linear);
		SetFloat(m_Shader->GetShaderProgramID(), ("u_PointLights[" + idx + "].Quadratic").c_str(), super::m_Lights.at(i)->Quadratic);
	}
	// materials
	for (int i = 0; i < MATERIALS; ++i)
	{
		std::string idx = std::to_string(i);
		SetVec3(m_Shader->GetShaderProgramID(), ("u_Material[" + idx + "].Ambient"), glm::vec3(super::m_Mats.at(i)->Ka[0], super::m_Mats.at(i)->Ka[1], super::m_Mats.at(i)->Ka[2]));
		SetVec3(m_Shader->GetShaderProgramID(), "u_Material[" + idx + "].Diffuse", glm::vec3(super::m_Mats.at(i)->Kd[0], super::m_Mats.at(i)->Kd[1], super::m_Mats.at(i)->Kd[2]));
		SetVec3(m_Shader->GetShaderProgramID(), "u_Material[" + idx + "].Specular", glm::vec3(super::m_Mats.at(i)->Ks[0], super::m_Mats.at(i)->Ks[1], super::m_Mats.at(i)->Ks[2]));
		SetFloat(m_Shader->GetShaderProgramID(), "u_Material[" + idx + "].Shininess", m_Mats.at(i)->n[0]);
	}
}
