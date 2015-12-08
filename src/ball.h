#pragma once

class ball {

  private:
    SDL_Texture* tex_ball;
    float pos_x;
    float pos_y;
    float speed_x;
    float speed_y;
    uint32_t last_tick;
    SDL_Renderer* renderer;

  public:
    ball(SDL_Renderer* renderer);
    void update();
    void render();
};
