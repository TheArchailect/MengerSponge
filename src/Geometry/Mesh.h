#pragma once
#include "../Core/include.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh
	(
		std::vector<Vertex> v, 
		std::vector<unsigned int> i
	);
	virtual ~Mesh() {};
	void Draw(GLenum ShaderPrimitive);
	void DrawLegacy();
	void DrawInstanced();
	void Update();
	glm::mat4 GetTransform() const;
	int GetElementCount();

private:
	std::vector<Vertex>			m_Verts;
	std::vector<unsigned int>	m_Indices;
	glm::vec3					m_Position;
	glm::vec3					m_Rotation;
	glm::mat4					m_Transform;
	unsigned int				VAO;
	unsigned int				VBO;
	unsigned int				EBO;
	void SetupMesh();
	glm::vec3 CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

};

