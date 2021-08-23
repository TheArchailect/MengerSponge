#pragma once
#include "Scene.h"
#include "../../Shaders/Shader.h"
#include "../../Shaders/ShaderProgram.h"


class InstancedGeometryGLSL : public Scene
{
public:
	InstancedGeometryGLSL(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

private:
	void RegisterCallbacks() override;
	void Update(glm::mat4 ModelTransform) override;

private:
	ShaderProgram* m_Shader;
};

