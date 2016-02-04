#pragma once

class ball {

  private:
    SDL_Texture* tex_ball;
    float pos_x;
    float pos_y;
    float speed_x;
    float speed_y;
    float collision_factor;
    uint32_t last_tick;
    SDL_Renderer* renderer;

  public:
    ball(SDL_Renderer* renderer);
    void reset(float start_side = 1.0);
    void update();
    int who_scored(int paddleL, int paddleR);
    void render();
  private:
    void inc_factor();
};
