#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "cleanup.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

void logError(const string &msg){
	cout << ">>> " << msg << " error" << std::endl;
}

void logSDLError(const string &msg){
	cout << ">>> " << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const string &path, SDL_Renderer* ren){

  SDL_Texture *texture = IMG_LoadTexture(ren, path.c_str());

  if (texture == nullptr){
    logSDLError("LoadTexture");
  }
  return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr) {

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != nullptr) {
    dst.w = clip->w;
    dst.h = clip->h;
  } else {
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
  }

  SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h, SDL_Rect* clip = nullptr) {

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;

  SDL_RenderCopy(ren, tex, clip, &dst);
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

  // aquire resources
  SDL_Texture* tex_bg = loadTexture("res/background.png", renderer);
  SDL_Texture* tex_ball = loadTexture("res/box.png", renderer);

  // ...
  SDL_Event e;
  bool quit = false;
  int ballX = 320 - 8;
  int ballY = 240 - 8;
  int paddleL = 16;
  int paddleR = 16;

  while (!quit) {
	// process input
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        //TODO multiple pressed keys do not work
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;
          case SDLK_w:
            if (paddleL > 16)
              paddleL -= 8;
            break;
          case SDLK_s:
            if (paddleL < 336)
              paddleL += 8;
            break;
          case SDLK_UP:
            if (paddleR > 16)
              paddleR -= 8;
            break;
          case SDLK_DOWN:
            if (paddleR < 336)
              paddleR += 8;
            break;
        }
      }
    }

	// delete screen
    SDL_RenderClear(renderer);

	// compose screen
    renderTexture(tex_bg, renderer, 0, 0);
    renderTexture(tex_ball, renderer, ballX, ballY, 16, 16);
	renderTexture(tex_ball, renderer,  16, paddleL, 16, 128);
	renderTexture(tex_ball, renderer, 608, paddleR, 16, 128);

	// update screen
    SDL_RenderPresent(renderer);
  }

  cleanup(renderer, window);
  SDL_Quit();

  return 0;
}
