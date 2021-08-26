#pragma once
#include "Core/include.h"

class DirectionalLight {
public:
	DirectionalLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s)
	{
		Lp = p;
		La = a;
		Ld = d;
		Ls = s;
	}
	glm::vec3 Lp;
	glm::vec3 La;
	glm::vec3 Ld;
	glm::vec3 Ls;
};

class PointLight {
public:
	PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s)
	{
		Constant = 1.0f;
		Linear = 0.09f;
		Quadratic = 0.032f;
		Position = p;
		Ambient = a;
		Diffuse = d;
		Specular = s;
	}
	glm::vec3 Position;
	float Constant;
	float Linear;
	float Quadratic;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
};