#include "textures.h"
#include "vector_screen.h"

vector_screen::vector_screen(SDL_Window* window, uint base_res)
: _window(window), _base_res(base_res), _windowed_base_res(base_res) {

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // TODO check if window is fullscreen
  _is_fullscreen = false;
}

vector_screen::~vector_screen() {

  SDL_DestroyRenderer(_renderer);
}

void vector_screen::update_res(uint base_res) {

  _base_res = base_res;
}

void vector_screen::toggle_fullscreen() {

  Uint32 win_flags = 0;

  if (_is_fullscreen) {
    // set to windowed mode
    SDL_SetWindowFullscreen(_window, win_flags);
    _base_res = _windowed_base_res;
    SDL_SetWindowSize(_window, _base_res, _base_res / 4 * 3);
    SDL_RenderSetScale(_renderer, 1.0, 1.0);
    _is_fullscreen = false;
  } else {
    // TODO change res for fullscreen
    // set to fullscreen mode
    win_flags = SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(_window, win_flags);
    _is_fullscreen = true;
  }

}

SDL_Texture* vector_screen::load_Texture(const std::string &path) {

  return loadTexture(path, _renderer);
}

SDL_Texture* vector_screen::loadText(const std::string &text, int font_size) {

  // white text is standard
  SDL_Color color = {255, 255, 255, 255};
  return renderText(text, "fonts/font.ttf", color, font_size, _renderer);
}

void vector_screen::render_Texture(float x, float y, float dim_x, float dim_y, SDL_Texture* tex) {

  int pix_x = x * _base_res;
  int pix_y = y * _base_res;
  int pix_w = dim_x * _base_res;
  int pix_h = dim_y * _base_res;

  renderTexture(tex, _renderer, pix_x, pix_y, pix_w, pix_h, nullptr);
}

void vector_screen::present() {

  SDL_RenderPresent(_renderer);
}

void vector_screen::clear() {
  SDL_RenderClear(_renderer);
}
