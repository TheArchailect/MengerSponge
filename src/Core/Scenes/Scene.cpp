#include "Scene.h"

Scene::Scene(int width, int height)
{
	RegisterCallbacks();
    b_IsActive = false;
	m_Camera = new Camera(width, height);
	CurrentSubdivision = 0;
	MengerSize = 20;
	Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
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
	m_Grid = new Mesh(GridVerts, GridIndices);

	// brass
	GLfloat brass_ambient[] = { 0.329412f, 0.223529f, 0.027451f,1.0f };
	GLfloat brass_diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
	GLfloat brass_specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
	GLfloat brass_shine = 27.8974f;

	// white rubber
	GLfloat wrubber_ambient[] = { 0.05f,0.05f,0.05f,1.0f };
	GLfloat wrubber_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
	GLfloat wrubber_specular[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat wrubber_shine = 10.0f;

	// black rubber
	GLfloat brubber_ambient[] = { 0.02f, 0.02f, 0.02f, 1.0f };
	GLfloat brubber_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
	GLfloat brubber_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat brubber_shine = 10.0f;

	// mats
	m_Mats.push_back(new Material(brass_ambient, brass_diffuse, brass_specular, brass_shine));
	m_Mats.push_back(new Material(wrubber_ambient, wrubber_diffuse, wrubber_specular, wrubber_shine));
	m_Mats.push_back(new Material(brubber_ambient, brubber_diffuse, brubber_specular, brubber_shine));
	
	// lights
	m_DirectionLight = new DirectionalLight
	(
		glm::vec3(-0.2, -1.0, -0.3), 
		glm::vec3(0.04f, 0.00f, 0.04f), 
		glm::vec3(0.7f, 0.0f, 0.7f), 
		glm::vec3(1.0f, 1.0f, 1.0f)
	);
	//m_Lights.push_back(new PointLight(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)));
	//m_Lights.push_back(new PointLight(glm::vec3(-28, 10, -5), glm::vec3(1, 0, 0), glm::vec3(1, 0.0, 0.3), glm::vec3(1, 1, 1)));
	//m_Lights.push_back(new PointLight(glm::vec3(50, -10, 5), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1)));
	//m_Lights.push_back(new PointLight(glm::vec3(-49, 10, 5), glm::vec3(.01, 0, .2), glm::vec3(1, 0, .2), glm::vec3(1, 1, 1)));
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
}

void Scene::GenerateLight(const Event<ApplicationEvent>& e)
{
	float rx = RandomFloat(-15, 15);
	float ry = RandomFloat(-15, 15);
	float rz = RandomFloat(-15, 15);

	float dr = RandomFloat(0, 1);
	float dg = RandomFloat(0, 1);
	float db = RandomFloat(0, 1);
	float ds = RandomFloat(0, 256);
	float div = 3.0;
	m_Lights.push_back
	(
		new PointLight
		(
			glm::vec3(rx, ry, rz), 
			glm::vec3(dr / div, dg / div, db / div), 
			glm::vec3(dr, dg, db), 
			glm::vec3(dr, dg, db)
		)
	);
	m_LightCount++;
}

float Scene::RandomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float x = max - min;
	float result = random * x;
	return min + result;
}

unsigned long Scene::GeometrySize()
{
	unsigned long value = (sizeof(Vertex) * m_Sponge.size());
    return value;
}

int Scene::TriangleCount()
{
	return m_VAO->GetElementCount() / 3;
}
