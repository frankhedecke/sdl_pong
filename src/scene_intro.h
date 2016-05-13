#pragma once

#include <SDL.h>

#include "scene.h"
#include "scene_manager.h"

class Scene_Intro : public Scene {

  private:
    SDL_Texture* _tex_bg;

  public:
    Scene_Intro(Scene_Manager* manager);
    ~Scene_Intro();
    void tick(bool &quit);
};
