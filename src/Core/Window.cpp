#include "Window.h"
#include "Application.h"
std::unique_ptr<Window> Window::Create(const WindowData& properties)
{
	std::cout << "Window constructor" << std::endl;
	return std::unique_ptr<Window>(new Window(properties));
}

Window::Window(const WindowData& properties)
{
	Init(properties);
	RegisterCallbacks();
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
	//ALT_CORE_INFO("Window Resize Event: {0}, {1}", e.windowWidth, e.windowHeight);
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
			std::cout << "SDL2 video subsystem couldn't be initialized. Error:" << std::endl;
			//ALT_CRITICAL("SDL2 video subsystem couldn't be initialized. Error: {0}", SDL_GetError());
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	m_Context = SDL_GL_CreateContext(m_Window);
	SDL_GL_MakeCurrent(m_Window, m_Context);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	//ALT_CORE_INFO("Loading GLAD: {0}", gladLoadGL());
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "glad load error" << std::endl;
	}

	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	//ALT_CORE_INFO
	//(
	//	"GL Renderer: {0}, "
	//	"GL Version: {1}, "
	//	"GLSL Version: {2}"
	//	, renderer, version, glslVersion
	//);
}

void Window::ShutDown(const Event<WindowEvent>& e)
{
	std::cout << "closing SDL2 window: " << std::endl;
	//ALT_CORE_WARNING("closing SDL2 window: {0}", m_Data.Title);
	SDL_DestroyWindow(m_Window);
	SDL_GL_DeleteContext(m_Context);
	SDL_Quit();
}
