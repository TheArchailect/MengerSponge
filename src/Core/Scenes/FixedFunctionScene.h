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
	void SetMaterial(const Material& m) override;
	void Lighting();
	
protected:
	void GeometryGenerate(const Event<ApplicationEvent>& e) override;

};

