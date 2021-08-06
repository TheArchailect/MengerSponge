#pragma once
#include "../../Geometry/Box.h"
#include "../include.h"
#include "../Camera.h"
class Scene
{
public: 
	Scene(int width, int height);
public:
	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Render() = 0;

public:
	void Generate(const Event<ApplicationEvent>& e);
	int GeometrySize();
	int Subdivision;

protected:
	std::vector<Box*> MengerSponge;
	Camera* m_Camera;
	typedef Scene super;

private:
	virtual void RegisterCallbacks();
	virtual void Update() = 0;
	
};

