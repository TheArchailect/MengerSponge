#pragma once
#include "Scene.h"
#include "Core/Components/InstancedMesh.h"

class InstancedGeometryGLSL : public Scene
{
public:
	InstancedGeometryGLSL(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;
	int TriangleCount() override;

private:
	void RegisterCallbacks() override;
	void Update() override;

private:
	ShaderProgram* m_Shader;
	InstancedMesh* m_IVAO;
};

