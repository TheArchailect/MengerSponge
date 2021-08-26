#pragma once
#include "Scene.h"
#include "Core/Components/Mesh.h"

class FixedFunctionScene : public Scene
{
public:
	FixedFunctionScene(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;
	int TriangleCount() override;

private:
	void RegisterCallbacks() override;
	void Update() override;
	void Lighting();
	
protected:
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

private:
	Mesh* m_VAO;

};

