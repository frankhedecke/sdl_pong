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
  // movement per second
  speed_x = 90;
  speed_y = 30;
  last_tick = SDL_GetTicks();
}

void ball::update() {
  uint32_t curr_tick = SDL_GetTicks();
  uint32_t prev_tick = last_tick;
  uint32_t diff = curr_tick - prev_tick;
  last_tick = curr_tick;

  // calc pos
  float step_x = speed_x * diff / 1000;
  float step_y = speed_y * diff / 1000;

  // update pos
  pos_x += step_x;
  pos_y += step_y;

  // update speed
  if (pos_x >= 600 || pos_x <= 40)
    speed_x *= -1;
  if (pos_y >= 472 || pos_y <=  8)
    speed_y *= -1;
}

void ball::render() {
  renderTexture(tex_ball, renderer, (int) pos_x - 8, (int) pos_y - 8, 16, 16);
}

// TODO cleanup texture
