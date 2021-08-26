#pragma once
#include "Scene.h"
#include "Core/Components/Mesh.h"

class CPUAnimatedGeometry : public Scene
{
public:
	CPUAnimatedGeometry(int width, int height);
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
	Mesh* m_VAO;
};