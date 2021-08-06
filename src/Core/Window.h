#pragma once
#include "include.h"
#include "../Event/EventManager.h"
struct WindowData // TO DO
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;
	bool VSync;
};

class Window
{
public:
	Window(const WindowData& properties, bool FullScreen);
	static std::unique_ptr<Window> Create(const WindowData& properties, bool FullScreen);
	void RegisterCallbacks();
	void Update();
	void WindowResize(const Event<WindowEvent>& e);
	uint32_t GetWidth() const { return m_Data.Width; }
	uint32_t GetHeight() const { return m_Data.Height; }
	inline void* GetNativeWindow() const { return m_Window; }
	void ShutDown(const Event<WindowEvent>& e);
	WindowData m_Data;

private:
	void Init(const WindowData& properties);
	SDL_Window* m_Window;
	SDL_GLContext m_Context;
	SDL_Renderer* m_Renderer;
};

