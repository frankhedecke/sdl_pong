#include "scene_intro.h"
#include "scene_pong.h"

void Scene_Intro::tick(bool &quit) {

  // render background
  _screen->render_Texture(0, 0, 1, 0.75, _tex_bg);
  _screen->present();

  SDL_Delay(1000);
  // load other scene
  Scene* pong = new Scene_Pong(_manager);
  _manager->load_scene(pong);

}

Scene_Intro::Scene_Intro(Scene_Manager* manager) : Scene(manager) {

  _tex_bg = _screen->load_Texture("res/background.png");

}

Scene_Intro::~Scene_Intro() {}
