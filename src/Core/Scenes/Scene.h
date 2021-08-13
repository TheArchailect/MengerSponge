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
	GLfloat n[0];
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
	int GeometrySize();
	int TriangleCount();
	unsigned int CurrentSubdivision;			

protected:
	void Subdivide(glm::vec3 Position, float s, int subd);
	void Compile(glm::vec3 origin, float size);

protected:
	Mesh* m_VAO;
	int IndexOffset;				
	std::vector<Vertex> m_Sponge;
	std::vector<unsigned int> m_Indices;
	Camera* m_Camera;				
	typedef Scene super;
	bool b_IsActive;
	Material* CyanPlastic;
	// lighting TO DO make class / struct
	GLfloat light_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[4] = { 1.0, 200.0, -100.0, 0.0 };

private:
	
	
};

