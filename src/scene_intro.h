#pragma once

#include <SDL.h>

#include "scene.h"
#include "scene_manager.h"

class Scene_Intro : public Scene {

  private:
    uint32_t _startup_ticks;
    SDL_Texture* _tex_bg;
    SDL_Texture* _tex_name;
    SDL_Texture* _tex_instr_left;
    SDL_Texture* _tex_instr_right;
  public:
    Scene_Intro(Scene_Manager* manager);
    ~Scene_Intro();
    void tick(bool &quit);
};
