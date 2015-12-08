#include <iostream>
#include <SDL.h>

#include "ball.h"
#include "textures.h"

using namespace std;

ball::ball(SDL_Renderer* ren) {
  renderer = ren;
  tex_ball = loadTexture("res/box.png", renderer);
  pos_x = 320;
  pos_y = 240;
  speed_x = 50;
  speed_y = 20;
}

void ball::update() {
  uint32_t curr_tick = SDL_GetTicks();
  uint32_t prev_tick = last_tick;
  uint32_t diff = curr_tick - prev_tick;

  cout << "ball at " << curr_tick << " with diff: " << diff << endl;

  last_tick = curr_tick;

  // TODO update position
}

void ball::render() {
  renderTexture(tex_ball, renderer, pos_x - 8, pos_y - 8, 16, 16);
}

// TODO cleanup texture
