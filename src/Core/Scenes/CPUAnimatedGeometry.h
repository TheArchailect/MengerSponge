#pragma once
#include "Scene.h"
#include "../../Shaders/Shader.h"
#include "../../Shaders/ShaderProgram.h"
class CPUAnimatedGeometry : public Scene
{
public:
	CPUAnimatedGeometry(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

private:
	void RegisterCallbacks() override;
	void Update(glm::mat4 ModelTransform) override;
	glm::vec3 SphereCast(glm::vec3 origin, glm::vec3 point, float radius);
	float Map(float value, float min1, float max1, float min2, float max2);

private:
	ShaderProgram* m_Shader;
	float EaseOut(float t);
};