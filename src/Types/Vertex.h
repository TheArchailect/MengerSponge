#pragma once
#include "Core/include.h"
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
