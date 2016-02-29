#pragma once

#include <SDL.h>
#include "textures.h"
#include "vector_screen.h"

class ball {

  private:
    SDL_Texture* tex_ball;
    float pos_x;
    float pos_y;
    float speed_x;
    float speed_y;
    float collision_factor;
    uint32_t last_tick;
    vector_screen* screen;

  public:
    ball(vector_screen* screen);
    void reset(float start_side = 1.0);
    void update();
    int who_scored(float paddleL, float paddleR);
    void render();
  private:
    void inc_factor();
};
