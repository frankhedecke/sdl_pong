#include <iostream>
#include <SDL.h>
#include "cleanup.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

void logError(const string &msg){
	cout << "> " << msg << " error" << std::endl;
}

void logSDLError(const string &msg){
	cout << "> " << msg << " error: " << SDL_GetError() << std::endl;
}

int init_main(SDL_Window* &window, SDL_Renderer* &renderer) {

  // init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    logSDLError("SDL_INIT");
    return 1;
  }

  window = SDL_CreateWindow("SDL Pong - press ESCAPE to exit", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    logSDLError("SDL_CreateWindow");
    SDL_Quit();
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == nullptr) {
    logSDLError("SDL_CreateRenderer");
    cleanup(window);
    SDL_Quit();
    return 1;
  }

  return 0;
}

int main(int argc, char** argv) {

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (init_main(window, renderer) != 0) {
    logError("init_main");
    return 1;
  }

  SDL_Event e;
  bool quit = false;

  while (!quit) {
	// process input
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;
        }
      }
    }

	// delete screen
    SDL_RenderClear(renderer);

	// update screen
    SDL_RenderPresent(renderer);
  }

  cleanup(renderer, window);
  SDL_Quit();

  return 0;
}
