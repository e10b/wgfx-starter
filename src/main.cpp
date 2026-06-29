#define WGPU_IMPLEMENTATION
#include <wgfx.h>

#include <iostream>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Could not initialize SDL3.\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("wgfx starter", 1280, 720, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Could not create SDL3 window.\n";
        SDL_Quit();
        return 1;
    }

    wgfx::init(wgfx::getSurface(window));

    wgfx::ColorTexture color;
    wgfx::RenderPass pass;
    pass.addTarget(&color);
    pass.setClear({0.05f, 0.06f, 0.08f, 1.f});

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
                running = false;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED || event.type == SDL_EVENT_WINDOW_EXPOSED) {
                wgfx::initSurface();
            }
        }

        wgfx::touch(&color);
        wgfx::start();

        pass.prepare();
        pass.end();

        wgfx::frame();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
