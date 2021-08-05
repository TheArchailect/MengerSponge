#pragma once
#include "include.h"
#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>
#include <stb/stb_image.h>
#include "Window.h"
#include "Input.h"
#include "EngineUtilities.h"

class Application
{
public:
	Application(unsigned int width, unsigned int height);
	virtual bool Init() = 0;
	virtual void Run() = 0;
	virtual void End(const Event<ApplicationEvent>& e) = 0;
	virtual void Tick() = 0;
	void Clear();

public:
	inline EngineUtils& GetUtils() { return *m_Utils; }
	inline Window& GetWindow() { return *m_Window; }
	static inline Application& Get() { return *s_Instance; }

protected:
	typedef Application super;
	bool m_FullScreen;
	Input* m_Input;
	EventManager* m_EventManager;
	bool b_IsRunning;

private:
	static EngineUtils* m_Utils;
	std::unique_ptr<Window> m_Window;
	static Application* s_Instance;

};
