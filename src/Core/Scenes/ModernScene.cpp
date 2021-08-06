#include "ModernScene.h"

ModernScene::ModernScene(int width, int height) : Scene(width, height)
{
	m_Shader = new ShaderProgram
	(
		"Shaders/Default.vert",
		"Shaders/Default.frag"
	);
	glUseProgram(m_Shader->GetShaderProgramID());
}

void ModernScene::Begin()
{

}

void ModernScene::End()
{

}

void ModernScene::Render()
{

}

void ModernScene::RegisterCallbacks()
{

}

void ModernScene::Update()
{
	// update uniforms
}
