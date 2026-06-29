#include "window.h"

Window::Window()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) { std::cout << "Couldn't init SDL!\n"; }
	window = SDL_CreateWindow("Learn WGFX", 1280, 720, SDL_WINDOW_RESIZABLE);
	wgfx::init(wgfx::getSurface(window));
}

void Window::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_WINDOW_RESIZED:
		{
			wgfx::initSurface();
			int width, height;
			SDL_GetWindowSize(window, &width, &height);
		}
		break;

		case SDL_EVENT_QUIT:
			close = true;
			break;

		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE) {
				close = true;
			}
			break;

		case SDL_EVENT_WINDOW_EXPOSED:
			wgfx::initSurface();
			break;
		}
	}
}

void Window::draw()
{
	wgfx::frame();
}