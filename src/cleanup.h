#pragma once

#include <utility>
#include <SDL.h>

template<typename T, typename... Args> 
void cleanup(T* t, Args&&... args) {
  cleanup(t);
  cleanup(std::forward<Args>(args)...);
}

template<>
void cleanup<SDL_Window>(SDL_Window* window) {
  if(!window)
    return;
  SDL_DestroyWindow(window);
}

template<>
void cleanup<SDL_Renderer>(SDL_Renderer* renderer) {
  if(!renderer)
    return;
  SDL_DestroyRenderer(renderer);
}

template<>
void cleanup<SDL_Texture>(SDL_Texture* texture) {
  if(!texture)
    return;
  SDL_DestroyTexture(texture);
}

template<>
void cleanup<SDL_Surface>(SDL_Surface* surface) {
  if(!surface)
    return;
  SDL_FreeSurface(surface);
}
