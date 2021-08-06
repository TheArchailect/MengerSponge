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

private:
	void RegisterCallbacks();
	void Update();

private:
	ShaderProgram* m_Shader;
};

