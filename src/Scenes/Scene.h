#pragma once
#include "Types/Vertex.h"
#include "Core/include.h"
#include "Core/Components/Camera.h"
#include "Shaders/Shader.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Components/Material.h"
#include "Application/Application.h"
#include "Utils/GeometryUtilities.h"
#include "Core/Components/Lighting.h"

#define MATERIALS 3
#define MAX_LIGHTS 100

class Scene
{
public: 
	Scene(int width, int height);
	int m_LightCount;
	int m_VertCount;

public:
	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Render() = 0;

private:
	virtual void RegisterCallbacks();
	virtual void Update() = 0;
	void GenerateLight(const Event<ApplicationEvent>& e);
	void DecrementLight(const Event<ApplicationEvent>& e);

protected:
	virtual void GeometryGenerate(const Event<ApplicationEvent>& e) = 0;

public:
	unsigned long GeometrySize();
	virtual int TriangleCount() = 0;
	uint32_t CurrentSubdivision;
	uint32_t MengerSize;

protected:
	void Subdivide(glm::vec3 Position, float s, int subd);
	void Compile(glm::vec3 origin, float size);

protected:
	//Mesh* m_Grid;
	int IndexOffset;				
	std::vector<Vertex> m_Sponge;
	std::vector<unsigned int> m_Indices;
	Camera* m_Camera;				
	typedef Scene super;
	bool b_IsActive;
	std::vector<PointLight*> m_Lights;
	std::vector<Material*> m_Mats;
	DirectionalLight* m_DirectionLight;

};

