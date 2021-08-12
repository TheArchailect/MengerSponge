#pragma once
#include "../../Geometry/Box.h"
#include "../include.h"
#include "../Camera.h"
#include "../../Geometry/Mesh.h"
class Scene
{
public: 
	Scene(int width, int height);
public:
	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Render() = 0;

private:
	virtual void RegisterCallbacks() = 0;
	virtual void Update() = 0;

protected:
	virtual void GeometryGenerate(const Event<ApplicationEvent>& e) = 0;

public:
	int GeometrySize();				// number of triangles in generated geo
	int CurrentSubdivision;			// level of detail

protected:
	void Subdivide(glm::vec3 Position, float s, int subd);				// parent geo generation TO DO
	void Compile(glm::vec3 origin, float size);
	glm::vec3 CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

protected:
	Mesh* m_VAO;
	int IndexOffset;				// used for geo generation / indexing	
	//std::vector<Box*> MengerSponge; // to be removed
	std::vector<Vertex> m_Sponge;
	std::vector<unsigned int> m_Indices;
	Camera* m_Camera;				
	typedef Scene super;
	bool b_IsActive;
	
};

