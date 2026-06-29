#define WGPU_IMPLEMENTATION
#include <wgfx.h>

#include <SDL3/SDL.h>
#include <iostream>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL3 init failed\n";
        return 1;
    }

    wgfx::init();
    std::cout << "SDL3 and wgfx initialized\n";

    SDL_Quit();
    return 0;
}
