#pragma once
#include "Core/Components/Material.h"
#include "Types/Vertex.h"
class InstancedMesh
{
public:
	InstancedMesh
	(
		std::vector<Vertex> v,
		std::vector<unsigned int> i
	);
	virtual ~InstancedMesh() {};
	void DrawInstanced();
	void Update();
	int GetElementCount();

private:
	std::vector<Vertex>			m_Verts;
	std::vector<unsigned int>	m_Indices;
	glm::vec3					m_Position;
	glm::vec3					m_Rotation;
	glm::mat4*					m_Transforms;
	unsigned int				VAO;
	unsigned int				VBO;
	unsigned int				EBO;
	unsigned int				MBO;
	uint32_t					m_Instances;

private:
	void SetupMesh();
};

