#include <iostream>

#include "ball.h"

using namespace std;

ball::ball(vector_screen* scr) {
  screen = scr;
  tex_ball = screen->load_Texture("res/box.png");
  reset();
  last_tick = SDL_GetTicks();
}

void ball::reset(float start_side) {
  pos_x = 0.5; // 320;
  pos_y = 0.375; // 240;
  // movement per second
  speed_x = 0.1875; // 120;
  speed_y = 0.0625; // 40;
  speed_x *= start_side;
  collision_factor = 1.0;
}

void ball::update() {
  uint32_t curr_tick = SDL_GetTicks();
  uint32_t prev_tick = last_tick;
  uint32_t diff = curr_tick - prev_tick;
  last_tick = curr_tick;

  // calc pos
  float step_x = speed_x * collision_factor * diff / 1000;
  float step_y = speed_y * collision_factor * diff / 1000;

  // update pos
  pos_x += step_x;
  pos_y += step_y;

}

int ball::who_scored(float paddleL, float paddleR) {

  if (pos_x <= 0.0625) { // 40
    if((pos_y - paddleL >= 0) && (pos_y - paddleL <= 0.2 )) { // 128
      // collision left
      speed_x *= -1;
      inc_factor();
    } else {
      return 1;
    }
  } 
  
  if (pos_x >= 0.9375) { // 600
    if((pos_y - paddleR >= 0) && (pos_y - paddleR <= 0.2 )) { // 128
      // collision right
      speed_x *= -1;
      inc_factor();
    } else {
      return 2;
    }
  } 
  
  if (pos_y >= 0.7375 || pos_y <=  0.0125) { // 472 || 8
    // collision top or bottom
    speed_y *= -1;
  }

  return 0;
}

void ball::render() {

  screen->render_Texture(pos_x - 0.0125, pos_y - 0.0125, 0.025, 0.025, tex_ball);
  // renderTexture(tex_ball, renderer, (int) pos_x - 8, (int) pos_y - 8, 16, 16);
}

void ball::inc_factor() {
  if (collision_factor < 2.0)
    collision_factor += 0.1;
}

// TODO cleanup texture or screen
