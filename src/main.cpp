#define WGPU_IMPLEMENTATION
#include <wgfx.h>

#include <SDL3/SDL.h>
#include <iostream>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL3 init failed\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("wgfx red window", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "SDL window creation failed\n";
        SDL_Quit();
        return 1;
    }

    wgpu::Surface surface = wgfx::getSurface(window);
    wgfx::init(surface);

    wgfx::ColorTexture backbuffer;
    wgfx::RenderPass redPass;
    redPass.addTarget(&backbuffer);
    redPass.setClear({ 1.0, 0.0, 0.0, 1.0 });

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        wgfx::start();
        wgfx::touch(&backbuffer);
        redPass.prepare();
        redPass.end();
        wgfx::frame();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
