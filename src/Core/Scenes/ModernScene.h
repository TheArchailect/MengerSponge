#pragma once
#include "Scene.h"
#include "../../Shaders/Shader.h"
#include "../../Shaders/ShaderProgram.h"


class ModernScene : public Scene
{
public:
	ModernScene(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

private:
	void RegisterCallbacks() override;
	void Update() override;

private:
	void SetupMesh(glm::vec3 Position, float s, int subd);
	//glm::vec3 CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	//void Subdivide(glm::vec3 origin, float size);
	
private:
	//std::vector<Vertex> m_Sponge;
	//std::vector<unsigned int> m_Indices;
	ShaderProgram* m_Shader;
	//Mesh* m_VAO;
};

