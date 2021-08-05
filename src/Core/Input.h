#pragma once
#include <sdl/SDL.h>
#include "../Event/EventManager.h"

	class Input
	{
	public:
		Input(SDL_Window* p_WindowInstance);
		void Update();
	private:
		SDL_Window* WindowInstance;
		bool b_FirstMouse;
	};


