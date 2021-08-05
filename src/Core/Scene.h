#pragma once
#include "../Geometry/Box.h"
#include "include.h"
#include "Camera.h"
class Scene
{
public:
	Scene(int width, int height);
	void Render();
	void Generate(const Event<ApplicationEvent>& e);
protected:
	typedef Scene super;
private:
	Camera* m_Camera;
	void RegisterCallbacks();
	void Update();
	std::vector<Box*> MengerSponge;
};

