#include "Scene.h"

Scene::Scene(int width, int height)
{
    b_IsActive = false;
	m_Camera = new Camera(width, height);
	CurrentSubdivision = 0;
	Subdivide(glm::vec3(0, 0, 0), 10, CurrentSubdivision);
	m_VAO = new Mesh(m_Sponge, m_Indices);
	
	// material setup
	float ambient[4] = { 0.0f, 0.1f, 0.06f, 1.0f };
	float diffuse[4] = { 0.0f,0.50980392f,0.50980392f,1.0f };
	float specular[4] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
	float shine = 32.0f;
	CyanPlastic = new Material(ambient, diffuse, specular, shine);
	// material end

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

int Scene::GeometrySize()
{
    return sizeof(glm::vec3) * m_Sponge.size();
}

int Scene::TriangleCount()
{
	return m_VAO->m_Indices.size() / 3;
}
