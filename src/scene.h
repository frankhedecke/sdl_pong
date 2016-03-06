#pragma once

#include <SDL.h>

#include "vector_screen.h"

class Scene {

  protected:
    vector_screen* _screen;

  private:
    void input(SDL_Event* event);
    void process();
    void output();

  public:
    Scene(vector_screen* screen);
    ~Scene();
    void tick(SDL_Event* event);
    void tick();
};
