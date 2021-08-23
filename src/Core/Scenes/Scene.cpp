#include "Scene.h"

Scene::Scene(int width, int height)
{
    b_IsActive = false;
	m_Camera = new Camera(width, height);
	CurrentSubdivision = 0;
	MengerSize = 20;
	Subdivide(glm::vec3(0, 0, 0), MengerSize, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
	
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

	// material setup
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess = 0.0;
	GLfloat low_shininess = 5.0;
	GLfloat high_shininess = 100.0;
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

	m_Mats.push_back(new Material(no_mat, mat_diffuse, no_mat, no_shininess));
	m_Mats.push_back(new Material(no_mat, mat_diffuse, mat_specular, low_shininess));
	m_Mats.push_back(new Material(mat_ambient, mat_diffuse, no_mat, no_shininess));
	// material end
	// lights
	m_Lights.push_back(new PointLight(glm::vec3(8, 10, -5), glm::vec3(.1, 0, .02), glm::vec3(1, 0, .2), glm::vec3(1, 1, 1)));
	m_Lights.push_back(new PointLight(glm::vec3(-8, 10, -5), glm::vec3(0, .1, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)));
	m_Lights.push_back(new PointLight(glm::vec3(0, -10, 5), glm::vec3(0, 0, .02), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1)));
	m_Lights.push_back(new PointLight(glm::vec3(0, 10, 5), glm::vec3(.01, 0, .2), glm::vec3(1, 0, .2), glm::vec3(1, 1, 1)));
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

unsigned long long Scene::GeometrySize()
{
	unsigned long value = (sizeof(Vertex) * m_Sponge.size());
    return value;
}

int Scene::TriangleCount()
{
	return m_VAO->m_Indices.size() / 3;
}
