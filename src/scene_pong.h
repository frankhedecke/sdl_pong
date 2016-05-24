#pragma once

#include <SDL.h>

#include "scene.h"
#include "scene_manager.h"

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
    int check_collision_score(float paddleL, float paddleR);
    void render();
  private:
    void inc_factor();
};

class Scene_Pong : public Scene {

  private:
    SDL_Texture* _tex_bg;
    SDL_Texture* _tex_box;
    ball* _ball;
    float _paddleL;
    float _paddleR;
    int _scoreL;
    int _scoreR ;
    // W, S, UP, DOWN, FULLSCREEN
    bool _keys[5];

    void input(SDL_Event* event);
    void process();
    void output();

  public:
    Scene_Pong(Scene_Manager* manager);
    ~Scene_Pong();
    void tick(bool &quit);
};
