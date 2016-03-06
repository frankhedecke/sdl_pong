#include "scene.h"

void Scene::input(SDL_Event* event) {}
void Scene::process() {}
void Scene::output() {}
void Scene::tick(SDL_Event* event) {

  input(event);
  process();
  output();
}

void Scene::tick() {

  process();
  output();
}

Scene::Scene(vector_screen* screen) : _screen(screen) {}

Scene::~Scene() {}
