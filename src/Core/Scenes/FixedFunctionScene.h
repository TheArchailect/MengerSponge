#pragma once
#include "Scene.h"
class FixedFunctionScene : public Scene
{
public:
	FixedFunctionScene(int width, int height);
	void Begin() override;
	void End() override;
	void Render() override;

private:
	void RegisterCallbacks() override;
	void Update() override;
	
protected:
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

};

