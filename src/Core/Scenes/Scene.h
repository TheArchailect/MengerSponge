#pragma once
#include "../../Geometry/Vertex.h"
#include "../include.h"
#include "../Camera.h"
#include "../../Geometry/Mesh.h"

class Material {
public:
	Material(float a[], float d[], float s[], float shininess)
	{
		for (int i = 0; i < 4; ++i)
		{
			Ka[i] = a[i];
			Kd[i] = d[i];
			Ks[i] = s[i];
		}
		n[0] = shininess;
	}
	GLfloat Ka[4];
	GLfloat Kd[4];
	GLfloat Ks[4];
	GLfloat n[1];
};

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
	virtual void SetMaterial(const Material& m) = 0;

public:
	unsigned long long GeometrySize();
	int TriangleCount();
	uint32_t CurrentSubdivision;
	uint32_t MengerSize;

protected:
	void Subdivide(glm::vec3 Position, float s, int subd);
	void Compile(glm::vec3 origin, float size);

protected:
	Mesh* m_VAO;
	Mesh* m_Grid;
	int IndexOffset;				
	std::vector<Vertex> m_Sponge;
	std::vector<unsigned int> m_Indices;
	Camera* m_Camera;				
	typedef Scene super;
	bool b_IsActive;

	Material* Mat1;
	Material* Mat2;
	Material* Mat3;
};

