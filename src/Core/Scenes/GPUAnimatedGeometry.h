#pragma once
#include "Scene.h"
#include "../../Shaders/Shader.h"
#include "../../Shaders/ShaderProgram.h"
class GPUAnimatedGeometry : public Scene
{
public:
	GPUAnimatedGeometry(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

private:
	void RegisterCallbacks() override;
	void Update() override;
	void SetMaterial(const Material& m) override;
	glm::vec3 SphereCast(glm::vec3 origin, glm::vec3 point, float radius);
	float Map(float value, float min1, float max1, float min2, float max2);

private:
	ShaderProgram* m_Shader;
	Mesh* m_Axis;
	float EaseOut(float t);
};

