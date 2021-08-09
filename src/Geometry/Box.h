#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

// replace this duplicate
class Vertex {
public:
	Vertex(glm::vec3 pos, glm::vec3 norm) : Position(pos), Normal(norm) {};
	glm::vec3 Position;
	glm::vec3 Normal;
	bool Equals(glm::vec3 search) {
		if
			(
				Position.x == search.x &&
				Position.y == search.y &&
				Position.z == search.z
				) return true;
		return false;
	}
};

class Box
{
public:
	Box(glm::vec3 pos, float s);
	void Draw();
	void Convert();
	std::vector<Box*> Generate();
	glm::vec3 CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	// conversion
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec3> Normals; 

private:
	std::vector<glm::vec3> v; // TO DO private: base set of verts for indexing
	glm::vec3 Normal;
	glm::vec3 Position;
	float Size;	
	std::vector<unsigned int> Indicies;
};

