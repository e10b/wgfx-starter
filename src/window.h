#pragma once

#include <wgfx.h>
#include <SDL3/SDL.h>

class Window {
public:
	static Window& Instance() {
		static Window instance;
		return instance;
	}

	Window();

	void update();

	void draw();

	bool close = false;
	SDL_Window* window;
};