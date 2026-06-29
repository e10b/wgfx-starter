cmake_minimum_required(VERSION 3.5...3.25)
project(wgfx_starter VERSION 0.1.0 LANGUAGES CXX C)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/sdl3)
add_subdirectory(deps/wgfx)

file(GLOB_RECURSE WGFX_STARTER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(wgfx_starter ${WGFX_STARTER_SOURCES})

target_link_libraries(wgfx_starter PRIVATE wgfx)

target_copy_webgpu_binaries(wgfx_starter)

set_target_properties(wgfx_starter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
