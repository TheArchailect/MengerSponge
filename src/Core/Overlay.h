#pragma once
#include "../Core/include.h"
#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>

class OverlayData {
public:
	OverlayData()
	{
		TriCount = 0;						// TO DO
		LightCount = 0;						// TO DO
		DepthBuffering = true;				// TO DO
		BackFaceCulling = true;				// TO DO
		Resolution = glm::vec2(800, 600);	// TO DO
		RefreshRate = "_";					// TO DO
		SceneNumber = 0;		// TO DO
		LOD = 1;							// TO DO 
		GeometrySize = 9;					// TO DO
	}

public:
	int TriCount;
	int LightCount;
	bool DepthBuffering;
	bool BackFaceCulling;
	glm::vec2 Resolution;
	std::string RefreshRate;
	int SceneNumber;
	int LOD;
	int GeometrySize;

};

class Overlay
{
public:
	Overlay();
	void Render(OVERLAY_STATE OverlayState);
	void End();
	OverlayData* m_OverlayData;

private:
	GLTtext* field;

};

