#include "Window.h"
#include "Application/Application.h"
std::unique_ptr<Window> Window::Create(const WindowData& properties, bool FullScreen)
{
	return std::unique_ptr<Window>(new Window(properties, FullScreen));
}

Window::Window(const WindowData& properties, bool FullScreen)
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_CUSTOM, SDL_LOG_PRIORITY_VERBOSE);
	vsync = true;
	Init(properties);
	RegisterCallbacks();
	if (FullScreen)
	{
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);		
	}
}

void Window::RegisterCallbacks()
{
	EventManager::Get().WindowDispatcher.Subscribe
	(
		WindowEvent::WINDOW_RESIZE,
		std::bind(&Window::WindowResize, this, std::placeholders::_1)
	);
	EventManager::Get().WindowDispatcher.Subscribe
	(
		WindowEvent::WINDOW_CLOSE,
		std::bind(&Window::ShutDown,
			this,
			std::placeholders::_1)
	);
}

void Window::Update()
{
	SDL_GL_SwapWindow(m_Window);
}

void Window::WindowResize(const Event<WindowEvent>& e)
{
	m_Data.Height = e.windowHeight;
	m_Data.Width = e.windowWidth;
	glViewport(0, 0, m_Data.Width, m_Data.Height);
	CameraViewportResize c(static_cast<float>(m_Data.Width), static_cast<float>(m_Data.Height));
	EventManager::Get().CameraDispatcher.Post(c);
}

void Window::Init(const WindowData& properties)
{
	bool b_SDLInitialised = false;
	m_Data.Title = properties.Title;
	m_Data.Width = properties.Width;
	m_Data.Height = properties.Height;

	if (!b_SDLInitialised)
	{
		
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_CUSTOM, "SDL2 video subsystem couldn't be initialized.");
		}
		else b_SDLInitialised = true;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_WindowFlags window_flags = (SDL_WindowFlags)
	(
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_ALLOW_HIGHDPI
	);

	m_Window = SDL_CreateWindow
	(
		m_Data.Title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Data.Width, m_Data.Height,
		window_flags
	);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	m_Context = SDL_GL_CreateContext(m_Window);
	SDL_GL_MakeCurrent(m_Window, m_Context);
	SDL_GL_SetSwapInterval(vsync);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_CUSTOM, "GLAD couldn't be initialized.");
	}

	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
}

void Window::ShutDown(const Event<WindowEvent>& e)
{
	SDL_DestroyWindow(m_Window);
	SDL_GL_DeleteContext(m_Context);
	SDL_Quit();
}