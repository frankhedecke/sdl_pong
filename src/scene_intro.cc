#include "scene_intro.h"
#include "scene_pong.h"

// TODO react to quit and window change event

void Scene_Intro::tick(bool &quit) {

  // render background
  _screen->render_Texture(0, 0, 1, 0.75, _tex_bg);
  // render text
  _screen->render_Texture(0.2, 0.1, 0.6, 0.1,  _tex_name);
  _screen->render_Texture(0.3, 0.3, 0.5, 0.06, _tex_instr_left);
  _screen->render_Texture(0.3, 0.5, 0.5, 0.06, _tex_instr_right);

  _screen->present();

  // wait 3 seconds
  uint32_t ticks = SDL_GetTicks();
  if ((ticks - _startup_ticks) > 3000) {
    Scene* pong = new Scene_Pong(_manager);
    _manager->load_scene(pong);
  }
}

Scene_Intro::Scene_Intro(Scene_Manager* manager) : Scene(manager) {

  _tex_bg = _screen->load_Texture("res/background.png");
  _tex_name = _screen->loadText("a pong clone made with SDL", 48);
  _tex_instr_left = _screen->loadText("left player: move paddles with W and S", 48);
  _tex_instr_right = _screen->loadText("right player: move paddles with UP and DOWN", 48);
  _startup_ticks = SDL_GetTicks();
}

Scene_Intro::~Scene_Intro() {}
