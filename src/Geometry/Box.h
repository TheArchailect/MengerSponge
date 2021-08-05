#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex
{
public:
	Vertex(glm::vec3 pos) : Position(pos) {}
	glm::vec3 Position;
};

class Box
{
public:
	Box(glm::vec3 pos, float s);
	void Draw();
	std::vector<Box*> Generate();
	glm::vec3 CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

private:
	glm::vec3 Position;
	std::vector<Vertex> v;
	float Size;
};

