#pragma once

class ball {

  private:
    SDL_Texture* tex_ball;
    int pos_x;
    int pos_y;
    float speed_x;
    float speed_y;
    uint32_t last_tick;
    SDL_Renderer* renderer;

  public:
    ball(SDL_Renderer* renderer);
    void update();
    void render();
};
