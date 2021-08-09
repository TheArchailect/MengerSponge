#pragma once
#include "Scene.h"
#include "../../Shaders/Shader.h"
#include "../../Shaders/ShaderProgram.h"
#include "../../Geometry/Mesh.h"

class ModernScene : public Scene
{
public:
	ModernScene(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

private:
	void SetupMesh();
	void RegisterCallbacks();
	void Update();

private:
	ShaderProgram* m_Shader;
	Mesh* m_VAO;
};

