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
					if (event.type == SDL_KEYDOWN)
					{
						WindowClosedEvent w;
						EventManager::Get().WindowDispatcher.Post(w);
						ApplicationEnd a;
						EventManager::Get().ApplicationDispatcher.Post(a);
					}
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
				
				// hud
				if (event.key.keysym.sym == SDLK_h && event.key.state == SDL_PRESSED)
				{
					ToggleProperties e;
					EventManager::Get().ApplicationDispatcher.Post(e);
				}

				// scene switch
				if 
					(
						event.key.keysym.sym == SDLK_1 || 
						event.key.keysym.sym == SDLK_2 ||
						event.key.keysym.sym == SDLK_3 ||
						event.key.keysym.sym == SDLK_4 ||
						event.key.keysym.sym == SDLK_5 ||
						event.key.keysym.sym == SDLK_6
					)
				{
					if (event.key.state == SDL_PRESSED)
					{
						int scene = 0;
						switch (event.key.keysym.sym)
						{
						case SDLK_1:
							scene = 0;
							break;
						case SDLK_2:
							scene = 1;
							break;
						case SDLK_3:
							scene = 2;
							break;
						case SDLK_4:
							scene = 3;
							break;
						case SDLK_5:
							scene = 4;
							break;
						case SDLK_6:
							scene = 5;
							break;
						}
						SwitchScene e((SCENE_NUMBER)scene);
						EventManager::Get().ApplicationDispatcher.Post(e);
					}

				}
				
				// subdivision
				if (event.key.keysym.sym == SDLK_PLUS || 
					event.key.keysym.sym == SDLK_EQUALS || 
					event.key.keysym.sym == SDLK_KP_PLUS)
				{
					if (event.type == SDL_KEYDOWN)
					{
						Generate e(1);
						EventManager::Get().ApplicationDispatcher.Post(e);
					}
				}
				if (event.key.keysym.sym == SDLK_KP_MINUS)
				{
					if (event.type == SDL_KEYDOWN)
					{
						Generate e(-1);
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
