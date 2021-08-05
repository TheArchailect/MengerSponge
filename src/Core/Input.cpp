#include "Input.h"
#include <iostream>

	Input::Input(SDL_Window* p_WindowInstance)
	{
		WindowInstance = p_WindowInstance;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	void Input::Update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if
				(
					event.type == SDL_WINDOWEVENT
					&& event.window.event == SDL_WINDOWEVENT_CLOSE
					&& event.window.windowID == SDL_GetWindowID(WindowInstance)
					|| event.type == SDL_QUIT
				)
			{
				if (event.type == SDL_KEYDOWN)
				{
					// first destroy all application instances
					ApplicationEnd a;
					EventManager::Get().ApplicationDispatcher.Post(a);
					// second shutdown glad / opengl / SDL2
					WindowClosedEvent w;
					EventManager::Get().WindowDispatcher.Post(w);
				}
			}
			if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(WindowInstance))
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					WindowResizeEvent e(event.window.data1, event.window.data2);
					EventManager::Get().WindowDispatcher.Post(e);
				}
			}
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			{
				bool b_UpdateCamera = event.type == SDL_KEYDOWN;
				if (event.key.keysym.sym == 27)
				{
					// first destroy all application instances
					ApplicationEnd a;
					EventManager::Get().ApplicationDispatcher.Post(a);
					// second shutdown glad / opengl / SDL2
					WindowClosedEvent w;
					EventManager::Get().WindowDispatcher.Post(w);
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					CameraLeft e(b_UpdateCamera);
					EventManager::Get().CameraDispatcher.Post(e);
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					CameraRight e(b_UpdateCamera);
					EventManager::Get().CameraDispatcher.Post(e);
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					CameraForward e(b_UpdateCamera);
					EventManager::Get().CameraDispatcher.Post(e);
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					CameraBackward e(b_UpdateCamera);
					EventManager::Get().CameraDispatcher.Post(e);
				}
				if (event.key.keysym.sym == SDLK_UP)
				{
					CameraUp e(b_UpdateCamera);
					EventManager::Get().CameraDispatcher.Post(e);
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					CameraDown e(b_UpdateCamera);
					EventManager::Get().CameraDispatcher.Post(e);
				}
				if (event.key.keysym.sym == SDLK_PLUS || 
					event.key.keysym.sym == SDLK_EQUALS || 
					event.key.keysym.sym == SDLK_KP_PLUS)
				{
					if (event.type == SDL_KEYDOWN)
					{
						Generate e;
						EventManager::Get().ApplicationDispatcher.Post(e);
					}
				}
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				CAMERA_ROTATION r;
				r.pitch = -event.motion.yrel;
				r.yaw = event.motion.xrel;
				CameraRotate e(r);
				EventManager::Get().CameraDispatcher.Post(e);
			}
		}
	}
