#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ball.h"
#include "cleanup.h"
#include "scene.h"
#include "scene_pong.h"
#include "vector_screen.h"

const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT =  768;

using namespace std;

int init_main(SDL_Window* &window, vector_screen* &screen) {

  // init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    logSDLError("SDL_INIT");
    return 1;
  }

  if (TTF_Init() != 0){
    logSDLError("TTF_Init");
    SDL_Quit();
    return 1;
  }

  int win_flags = SDL_WINDOW_SHOWN + SDL_WINDOW_RESIZABLE;
  window = SDL_CreateWindow("SDL Pong - press ESCAPE to exit", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);

  if (window == nullptr) {
    logSDLError("SDL_CreateWindow");
    SDL_Quit();
    return 1;
  }

  int width = 0;
  SDL_GetWindowSize(window, &width, nullptr);
  screen = new vector_screen(window, width);

  return 0;
}

int main(int argc, char** argv) {

  SDL_Window *window = nullptr;
  vector_screen *screen = nullptr;
  Scene_Pong *scene_pong = nullptr;

  if (init_main(window, screen) != 0) {
    logError("init_main");
    return 1;
  }

  scene_pong = new Scene_Pong(screen);

  bool quit = false;

  while (!quit) {
    scene_pong->tick(quit);
  }

  cleanup(window);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
