#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "ball.h"
#include "cleanup.h"
#include "textures.h"
#include "vector_screen.h"

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
// TODO const int for paddle dimensions

// TODO delete pixel numbers in comments

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

  window = SDL_CreateWindow("SDL Pong - press ESCAPE to exit", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    logSDLError("SDL_CreateWindow");
    SDL_Quit();
    return 1;
  }

  screen = new vector_screen(window, 1.0, 0.75);
  screen->update_res(SCREEN_WIDTH, SCREEN_HEIGHT);

  return 0;
}

int main(int argc, char** argv) {

  SDL_Window *window = nullptr;
  vector_screen *screen = nullptr;

  if (init_main(window, screen) != 0) {
    logError("init_main");
    return 1;
  }

  int text_size = 24;

  SDL_Texture* tex_bg  = screen->load_Texture("res/background.png");
  SDL_Texture* tex_box = screen->load_Texture("res/box.png");

  // ...
  SDL_Event e;
  ball* b = new ball(screen);
  bool quit = false;
  float paddleL = 0.275; // 176 = 240 - 64
  float paddleR = 0.275; // 176 = 240 - 64
  int scoreL = 0;
  int scoreR = 0;
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
      if (paddleL > 0.025) // 16
        paddleL -= 0.00625; // 4
    if (keys[1])
      if (paddleL < 0.525) // 336
        paddleL += 0.00625;
    if (keys[2])
      if (paddleR > 0.025)
        paddleR -= 0.00625;
    if (keys[3])
      if (paddleR < 0.525)
        paddleR += 0.00625;

    // clear screen
    screen->clear();

    // compose screen background
    screen->render_Texture(0, 0, 1, 0.75, tex_bg);
    screen->render_Texture(0.025, paddleL, 0.025, 0.2, tex_box);
    screen->render_Texture(0.950, paddleR, 0.025, 0.2, tex_box);

    // check for collisions
    b->update();
    switch ( b->who_scored(paddleL, paddleR) ) {
      case 0: break;
      case 1: 
        scoreR++;
        b->reset(-1.0);
        break;
      case 2:
        scoreL++;
        b->reset(1.0);
        break;
      default: break;
    }

    // render score
    string score;
    score.append( to_string(scoreL) );
    score.append( " : " );
    score.append( to_string(scoreR) );

    SDL_Texture* tex_score = screen->loadText(score, text_size);
    // TODO rework dimensions
    screen->render_Texture(0.475, 0.03, 0.05, 0.03, tex_score);

    cleanup(tex_score);

    // render ball
    b->render();

    // update screen
    screen->present();
  }

  cleanup(tex_bg, tex_box);
  cleanup(window);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
