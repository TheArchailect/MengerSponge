#include "Scene.h"

Scene::Scene(int width, int height)
{
	RegisterCallbacks();
    b_IsActive = false;
	m_Camera = new Camera(width, height);
	CurrentSubdivision = 0;
	MengerSize = 20;
	Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
	m_VertCount = m_Sponge.size();
	m_LightCount = 0;
	std::vector<Vertex> GridVerts;
	std::vector<uint32_t> GridIndices;
	int gwidth = 1;
	int gdepth = 1;

	GridVerts.push_back(Vertex(glm::vec3(gwidth, -10, -gdepth), glm::vec3(0, 1, 0)));
	GridVerts.push_back(Vertex(glm::vec3(-gwidth, -10, gdepth), glm::vec3(0, 1, 0)));
	GridVerts.push_back(Vertex(glm::vec3(-gwidth, -10, -gdepth), glm::vec3(0, 1, 0)));
	GridVerts.push_back(Vertex(glm::vec3(gwidth, -10, -gdepth), glm::vec3(0, 1, 0)));
	GridVerts.push_back(Vertex(glm::vec3(gwidth, -10, gdepth), glm::vec3(0, 1, 0)));
	GridVerts.push_back(Vertex(glm::vec3(-gwidth, -10, gdepth), glm::vec3(0, 1, 0)));
	
	for (int i = 2; i < GridVerts.size(); i += 3)
	{
		GridIndices.push_back(i);
		GridIndices.push_back(i - 1);
		GridIndices.push_back(i - 2);
	}

	// 
	GLfloat brass_ambient[] = { 0.329412f, 0.223529f, 0.027451f,1.0f };
	GLfloat brass_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
	GLfloat brass_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
	GLfloat brass_shine = 32.0f;

	// 
	GLfloat wrubber_ambient[] = { 0.05f,0.05f,0.05f,1.0f };
	GLfloat wrubber_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
	GLfloat wrubber_specular[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat wrubber_shine = 32.0f;

	// 
	GLfloat brubber_ambient[] = { 0.15f, 0.15f, 0.15f, 1.0f };
	GLfloat brubber_diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat brubber_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
	GLfloat brubber_shine = 128.0f;

	// mats
	m_Mats.push_back(new Material(brass_ambient, brass_diffuse, brass_specular, brass_shine));
	m_Mats.push_back(new Material(wrubber_ambient, wrubber_diffuse, wrubber_specular, wrubber_shine));
	m_Mats.push_back(new Material(brubber_ambient, brubber_diffuse, brubber_specular, brubber_shine));
	
	// lights
	m_DirectionLight = new DirectionalLight
	(
		glm::vec3(0, 0, 0), 
		glm::vec3(0.366f, 0.366f, 0.366f),
		glm::vec3(0.56f, 0.56f, 0.56f),
		glm::vec3(0.2f, 0.2f, 0.2f)
	);
}

void Scene::Subdivide(glm::vec3 Position, float s, int subd)
{
	for (int x = -1; x < 2; ++x)
	{
		for (int y = -1; y < 2; ++y)
		{
			for (int z = -1; z < 2; ++z)
			{
				int check = abs(x) + abs(y) + abs(z);
				if (check > 1)
				{
					float Size = (s / 3);
					glm::vec3 Origin = glm::vec3
					(
						Position.x + x * Size,
						Position.y + y * Size,
						Position.z + z * Size
					);
					if (subd > 0) Subdivide(Origin, Size, subd - 1);
					else
					{
						Compile(Origin, Size / 2);
						IndexOffset++;
					}
				}
			}
		}
	}
	m_VertCount = m_Sponge.size();
}

void Scene::Compile(glm::vec3 origin, float size)
{
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x + size, origin.y - size, origin.z - size),
		glm::vec3(0, 1, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x + size, origin.y + size, origin.z - size),
		glm::vec3(0, 1, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x + size, origin.y + size, origin.z + size),
		glm::vec3(0, 0, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x + size, origin.y - size, origin.z + size),
		glm::vec3(0, 0, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x - size, origin.y - size, origin.z - size),
		glm::vec3(0, 0, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x - size, origin.y - size, origin.z + size),
		glm::vec3(0, 0, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x - size, origin.y + size, origin.z + size),
		glm::vec3(0, 0, 0))
	);
	m_Sponge.push_back(Vertex
	(
		glm::vec3(origin.x - size, origin.y + size, origin.z - size),
		glm::vec3(0, 0, 0))
	);

	m_Indices.push_back(0 + (8 * IndexOffset));
	m_Indices.push_back(1 + (8 * IndexOffset));
	m_Indices.push_back(3 + (8 * IndexOffset));
	m_Indices.push_back(1 + (8 * IndexOffset));
	m_Indices.push_back(2 + (8 * IndexOffset));
	m_Indices.push_back(3 + (8 * IndexOffset));

	m_Indices.push_back(3 + (8 * IndexOffset));
	m_Indices.push_back(2 + (8 * IndexOffset));
	m_Indices.push_back(5 + (8 * IndexOffset));
	m_Indices.push_back(2 + (8 * IndexOffset));
	m_Indices.push_back(6 + (8 * IndexOffset));
	m_Indices.push_back(5 + (8 * IndexOffset));

	m_Indices.push_back(4 + (8 * IndexOffset));
	m_Indices.push_back(0 + (8 * IndexOffset));
	m_Indices.push_back(5 + (8 * IndexOffset));
	m_Indices.push_back(5 + (8 * IndexOffset));
	m_Indices.push_back(0 + (8 * IndexOffset));
	m_Indices.push_back(3 + (8 * IndexOffset));

	m_Indices.push_back(1 + (8 * IndexOffset));
	m_Indices.push_back(7 + (8 * IndexOffset));
	m_Indices.push_back(6 + (8 * IndexOffset));
	m_Indices.push_back(1 + (8 * IndexOffset));
	m_Indices.push_back(6 + (8 * IndexOffset));
	m_Indices.push_back(2 + (8 * IndexOffset));

	m_Indices.push_back(7 + (8 * IndexOffset));
	m_Indices.push_back(4 + (8 * IndexOffset));
	m_Indices.push_back(5 + (8 * IndexOffset));
	m_Indices.push_back(7 + (8 * IndexOffset));
	m_Indices.push_back(5 + (8 * IndexOffset));
	m_Indices.push_back(6 + (8 * IndexOffset));

	m_Indices.push_back(7 + (8 * IndexOffset));
	m_Indices.push_back(1 + (8 * IndexOffset));
	m_Indices.push_back(0 + (8 * IndexOffset));
	m_Indices.push_back(7 + (8 * IndexOffset));
	m_Indices.push_back(0 + (8 * IndexOffset));
	m_Indices.push_back(4 + (8 * IndexOffset));
}

void Scene::RegisterCallbacks()
{
	EventManager::Get().ApplicationDispatcher.Subscribe
	(
		ApplicationEvent::ADD_LIGHT,
		std::bind
		(
			&Scene::GenerateLight,
			this,
			std::placeholders::_1
		)
	);
	EventManager::Get().ApplicationDispatcher.Subscribe
	(
		ApplicationEvent::REMOVE_LIGHT,
		std::bind
		(
			&Scene::DecrementLight,
			this,
			std::placeholders::_1
		)
	);
}

void Scene::GenerateLight(const Event<ApplicationEvent>& e)
{
	if (super::b_IsActive)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", e.GetName().c_str());
		if (m_LightCount < MAX_LIGHTS)
		{
			float R = 85;
			float dr = RandomFloat(0, 1);
			float dg = RandomFloat(0, 1);
			float db = RandomFloat(0, 1);
			float ds = RandomFloat(0, 256);
			float div = 3.0;
			m_Lights.push_back
			(
				new PointLight
				(
					SphericalDistribution() * R,
					glm::vec3(dr / div, dg / div, db / div),
					glm::vec3(dr, dg, db),
					glm::vec3(dr, dg, db)
				)
			);
			m_LightCount++;
		}
	}

}

void Scene::DecrementLight(const Event<ApplicationEvent>& e)
{
	if (super::b_IsActive)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s", e.GetName().c_str());
		if (m_LightCount > 0)
		{
			m_Lights.erase(m_Lights.begin() + m_Lights.size() - 1);
			m_LightCount--;
		}
	}
}

unsigned long Scene::GeometrySize()
{
	unsigned long value = (sizeof(Vertex) * m_Sponge.size());
    return value;
}
