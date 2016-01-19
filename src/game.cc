#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ball.h"
#include "cleanup.h"
#include "textures.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

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

  // aquire resources
  SDL_Texture* tex_bg = loadTexture("res/background.png", renderer);
  SDL_Texture* tex_box = loadTexture("res/box.png", renderer);

  // ...
  SDL_Event e;
  ball* b = new ball(renderer);
  bool quit = false;
  int ballX = 320 - 8;
  int ballY = 240 - 8;
  int paddleL = 16;
  int paddleR = 16;
  // W, S, UP, DOWN
  bool keys[4] = {false};

  while (!quit) {
	// process input
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
          case SDLK_ESCAPE:  quit = true; break;
          case SDLK_w:    keys[0] = true; break;
          case SDLK_s:    keys[1] = true; break;
          case SDLK_UP:   keys[2] = true; break;
          case SDLK_DOWN: keys[3] = true; break;
        }
      } else if (e.type == SDL_KEYUP) {
        switch(e.key.keysym.sym) {
          case SDLK_w:    keys[0] = false; break;
          case SDLK_s:    keys[1] = false; break;
          case SDLK_UP:   keys[2] = false; break;
          case SDLK_DOWN: keys[3] = false; break;
        }
      }
    }

    // move paddles 
    if (keys[0])
      if (paddleL > 16)
        paddleL -=4;
    if (keys[1])
      if (paddleL < 336)
        paddleL +=4;
    if (keys[2])
      if (paddleR > 16)
        paddleR -=4;
    if (keys[3])
      if (paddleR < 336)
        paddleR +=4;
   
    // delete screen
    SDL_RenderClear(renderer);

    // compose screen background
    renderTexture(tex_bg, renderer, 0, 0);
    renderTexture(tex_box, renderer,  16, paddleL, 16, 128);
    renderTexture(tex_box, renderer, 608, paddleR, 16, 128);

    // render ball
    b->update();
    b->render();

    // update screen
    SDL_RenderPresent(renderer);
  }

  cleanup(tex_bg, tex_box);
  cleanup(renderer, window);
  SDL_Quit();

  return 0;
}
