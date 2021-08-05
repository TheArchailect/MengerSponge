#pragma once
#include "include.h"
class EngineUtils {
public:
	EngineUtils()
	{
		m_LastTime = 0;
		m_DeltaTime = 0;
		m_FPS = 0.0;
		m_FPS_LastTime = 0.0;
		m_FrameCount = 0;
	}

	void DeltaTime()
	{
		float CurrentTime = SDL_GetTicks() / 1000.0f;
		m_DeltaTime = CurrentTime - m_LastTime;
		m_LastTime = CurrentTime;
	}

	void FrameRate()
	{
		m_FrameCount++;
		float CurrentTime = SDL_GetTicks() / 1000.0f;
		if (CurrentTime - m_FPS_LastTime > 1.0f)
		{
			m_FPS = m_FrameCount / (CurrentTime - m_FPS_LastTime);
			m_FPS_LastTime = CurrentTime;
			m_FrameCount = 0;
		}
	}
	float m_DeltaTime;
	float m_FPS;

private:
	float m_LastTime;
	float m_FPS_LastTime;
	int m_FrameCount;

};