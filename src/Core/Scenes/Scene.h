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
	int GeometrySize();
	int Subdivision;

protected:
	void Generate();
	virtual void GeometryGenerate(const Event<ApplicationEvent>& e) = 0;
	std::vector<Box*> MengerSponge;
	Camera* m_Camera;
	typedef Scene super;
	bool b_IsActive;

private:
	virtual void RegisterCallbacks();
	virtual void Update() = 0;
	
};

