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
	void RegisterCallbacks();
	void Update();

};

