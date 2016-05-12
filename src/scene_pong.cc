#include "cleanup.h"
#include "scene_pong.h"

void Scene_Pong::input(SDL_Event* event) {

  if (event->type == SDL_KEYDOWN) {
    switch(event->key.keysym.sym) {
      case SDLK_w:    _keys[0] = true; break;
      case SDLK_s:    _keys[1] = true; break;
      case SDLK_i:    _keys[2] = true; break;
      case SDLK_k:    _keys[3] = true; break;
      case SDLK_UP:   _keys[2] = true; break;
      case SDLK_DOWN: _keys[3] = true; break;
    }
  } else if (event->type == SDL_KEYUP) {
    // TODO check if buttons are pressed or already are released
    switch(event->key.keysym.sym) {
      case SDLK_w:    _keys[0] = false; break;
      case SDLK_s:    _keys[1] = false; break;
      case SDLK_i:    _keys[2] = false; break;
      case SDLK_k:    _keys[3] = false; break;
      case SDLK_UP:   _keys[2] = false; break;
      case SDLK_DOWN: _keys[3] = false; break;
    }
  }
}

void Scene_Pong::process() {

  // move paddles 
  if (_keys[0])
    if (_paddleL > 0.025)
      _paddleL -= 0.00625;
  if (_keys[1])
    if (_paddleL < 0.525)
      _paddleL += 0.00625;
  if (_keys[2])
    if (_paddleR > 0.025)
      _paddleR -= 0.00625;
  if (_keys[3])
    if (_paddleR < 0.525)
      _paddleR += 0.00625;

  // check for collisions
  _ball->update();
  switch ( _ball->who_scored(_paddleL, _paddleR) ) {
    case 0: break;
    case 1: 
      _scoreR++;
      _ball->reset(-1.0);
      break;
    case 2:
      _scoreL++;
      _ball->reset(1.0);
      break;
    default: break;
  }

  // clear screen
  _screen->clear();

  // compose screen background
  _screen->render_Texture(0    ,        0,     1, 0.75, _tex_bg);
  _screen->render_Texture(0.025, _paddleL, 0.025,  0.2, _tex_box);
  _screen->render_Texture(0.950, _paddleR, 0.025,  0.2, _tex_box);

  // render score
  std::string score;
  score.append( std::to_string(_scoreL) );
  score.append( " : " );
  score.append( std::to_string(_scoreR) );
  SDL_Texture* tex_score = _screen->loadText(score, 24);
  // TODO rework dimensions
  _screen->render_Texture(0.475, 0.03, 0.05, 0.03, tex_score);
  cleanup(tex_score);

  // render ball
  _ball->render();
}

void Scene_Pong::output() {

  _screen->present();
}

/* TODO delete
void Scene_Pong::tick() {

  process();
  output();
} */

void Scene_Pong::tick(bool &quit) {

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

// TODO delete
// Scene_Pong::Scene_Pong(vector_screen* screen) : Scene(screen) {
Scene_Pong::Scene_Pong(Scene_Manager* manager) : Scene(manager) {

  _tex_bg  = _screen->load_Texture("res/background.png");
  _tex_box = _screen->load_Texture("res/box.png");
  _ball = new ball(_screen);
  _paddleL = 0.275;
  _paddleR = 0.275;
  _scoreL = 0;
  _scoreR = 0;
  // W, S, UP, DOWN, FULLSCREEN
  for (int i = 0; i < 5; ++i)
    _keys[i] = false;
}
