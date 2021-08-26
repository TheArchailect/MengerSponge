#pragma once
#include "Core/include.h"
#include <stb/stb_image.h>
#include "Core/Window.h"
#include "Core/Input.h"
#include "Utils/EngineUtilities.h"
#include "Core/Components/Material.h"

class Application
{
public:
	Application(uint32_t width, uint32_t height);
	virtual void Run() = 0;
	virtual void Init();
	// temp
	bool b_Lighting;

private:
	virtual void Tick() = 0;
	void RegisterCallbacks();
	void ToggleLighting(const Event<ApplicationEvent>& e);
	void ToggleBackfaceCulling(const Event<ApplicationEvent>& e);
	void ToggleDepthBuffer(const Event<ApplicationEvent>& e);

protected:
	void Clear();
	virtual void End(const Event<ApplicationEvent>& e) = 0;

public:
	inline EngineUtils& GetUtils() { return *m_Utils; }
	inline Window& GetWindow() { return *m_Window; }
	static inline Application& Get() { return *s_Instance; }

protected:
	std::unique_ptr<Window> m_Window;
	typedef Application super;
	bool m_FullScreen;
	Input* m_Input;
	EventManager* m_EventManager;
	bool b_IsRunning;
	bool b_BackFaceCulling;
	bool b_DepthTesting;
	

private:
	static EngineUtils* m_Utils;
	static Application* s_Instance;

};
