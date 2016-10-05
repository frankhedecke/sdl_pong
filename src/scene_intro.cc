#include "scene_intro.h"
#include "scene_pong.h"

void Scene_Intro::input(SDL_Event* event) {}

void Scene_Intro::process() {

  // clear screen
  _screen->clear();

  // render background
  _screen->render_Texture(0, 0, 1, 0.75, _tex_bg);
  // render text
  _screen->render_Texture(0.2, 0.1, 0.6, 0.1,  _tex_name);
  _screen->render_Texture(0.3, 0.3, 0.5, 0.06, _tex_instr_left);
  _screen->render_Texture(0.3, 0.5, 0.5, 0.06, _tex_instr_right);

  // wait 3 seconds
  uint32_t ticks = SDL_GetTicks();
  if ((ticks - _startup_ticks) > 3000) {
    Scene* pong = new Scene_Pong(_manager);
    _manager->load_scene(pong);
  }
}

void Scene_Intro::output() {

  _screen->present();
}


void Scene_Intro::tick(bool &quit) {

  SDL_Event e;
  
  // loop will be entered if an event occurrs
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
             quit = true; break;
        case SDLK_f:
             _keys[4] = true; break;
      }
    } else if (e.type == SDL_KEYUP) {
      if (e.key.keysym.sym == SDLK_f && _keys[4]) {
         _keys[4] = false;
         _screen->toggle_fullscreen(); 
      }

    } else if (e.type == SDL_WINDOWEVENT) {
       if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
         _screen->update_res();
       }
    }

    input(&e);
  }

  process();
  output();
}

Scene_Intro::Scene_Intro(Scene_Manager* manager) : Scene(manager) {

  _tex_bg = _screen->load_Texture("res/background.png");
  _tex_name = _screen->loadText("a pong clone made with SDL", 48);
  _tex_instr_left = _screen->loadText("left player: move paddles with W and S", 48);
  _tex_instr_right = _screen->loadText("right player: move paddles with UP and DOWN", 48);
  _startup_ticks = SDL_GetTicks();
  _keys[0] = false;
}

Scene_Intro::~Scene_Intro() {}
