#pragma once

#include <SDL.h>

#include "ball.h"
#include "scene.h"
#include "vector_screen.h"

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
    // TODO delete
    // Scene_Pong(vector_screen* screen);
    ~Scene_Pong();
    // void tick();
    void tick(bool &quit);
};
