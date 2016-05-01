#include <iostream>
#include "textures.h"
#include "vector_screen.h"

// TODO problem: ratio 4 : 3 is hardcoded
// TODO refactor everything

vector_screen::vector_screen(SDL_Window* window, uint res_x)
: _window(window), _windowed_base_res(res_x), _windowed_bup_res(res_x) {

  // calculate fullscreen parameters
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  _fs_res_x = mode.w;
  _fs_res_y = mode.h;
  std::cout << "display: " << _fs_res_x << "x" << _fs_res_y << std::endl;
  _fs_res = 0;
  _fs_offset_x = 0;
  _fs_offset_y = 0;
  // TODO move to extra function
  if ( (_fs_res_x * 3) == (_fs_res_y * 4) ) {
    _fs_res = _fs_res_x;
  } else if ( (_fs_res_x * 3) > (_fs_res_y * 4) ) {
    _fs_res = _fs_res_y * 4 / 3;
    _fs_offset_x = (_fs_res_x - _fs_res) / 2;
  } else {
    _fs_res = _fs_res_x;
    _fs_offset_y = (_fs_res_y - _fs_res_x * 3 / 4) / 2 ;
  }
  std::cout << "fullscreen base res: " << _fs_res << " with offsets: " << _fs_offset_x << " + " << _fs_offset_y<< std::endl;
  // calculate window parameters
  int w, h = 0;
  SDL_GetWindowSize(_window, &w, &h);
  _res_x = w;
  _res_y = h;
  _res = 0;
  _offset_x = 0;
  _offset_y = 0;
  if ( (_res_x * 3) == (_res_y * 4) ) {
    _res = _res_x;
  } else if ( (_res_x * 3) > (_res_y * 4) ) {
    _res = _res_y * 4 / 3;
    _offset_x = (_res_x - _res) / 2;
  } else {
    _res = _res_x;
    _offset_y = (_res_y - _res_x * 3 / 4) / 2 ;
  }

  std::cout << "window base res: " << _res << " with offsets: " << _offset_x << " + " << _offset_y<< std::endl;

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // TODO check if window is fullscreen
  _is_fullscreen = false;
}

vector_screen::~vector_screen() {

  SDL_DestroyRenderer(_renderer);
}

void vector_screen::update_res() {
  // the _windowed_base_res changes if fullscreen is entered
  // but changes back if fullscreen is left
  // after changing to fullscreen and back the resolution is different
  int w, h = 0;
  SDL_GetWindowSize(_window, &w, &h);
  _res_x = w;
  _res_y = h;
  _res = 0;
  _offset_x = 0;
  _offset_y = 0;
  if ( (_res_x * 3) == (_res_y * 4) ) {
    _res = _res_x;
  } else if ( (_res_x * 3) > (_res_y * 4) ) {
    _res = _res_y * 4 / 3;
    _offset_x = (_res_x - _res) / 2;
  } else {
    _res = _res_x;
    _offset_y = (_res_y - _res_x * 3 / 4) / 2 ;
  }
}

void vector_screen::toggle_fullscreen() {

  Uint32 win_flags = 0;

  if (_is_fullscreen) {
    // restore window resolution
    _windowed_base_res = _windowed_bup_res;
    // set to windowed mode
    SDL_SetWindowFullscreen(_window, win_flags);
    SDL_SetWindowSize(_window, _windowed_base_res, _windowed_base_res / 4 * 3);
    SDL_RenderSetScale(_renderer, 1.0, 1.0);

    _is_fullscreen = false;
  } else {
    // backup window resolution
    int w = 0;
    SDL_GetWindowSize(_window, &w, nullptr);
    _windowed_bup_res = w;
    // set to fullscreen mode
    win_flags = SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowSize(_window, _fs_res_x, _fs_res_y);
    SDL_SetWindowFullscreen(_window, win_flags);
    SDL_RenderSetScale(_renderer, 1.0, 1.0);

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

  int res = 640;
  int off_x = 0;
  int off_y = 0;

  if (_is_fullscreen) {
    res = _fs_res;
    off_x = _fs_offset_x;
    off_y = _fs_offset_y;
  } else {
    res = _res;
    off_x = _offset_x;
    off_y = _offset_y;
  }

  int pix_x = x * res + off_x;
  int pix_y = y * res + off_y;
  int pix_w = dim_x * res;
  int pix_h = dim_y * res;

  renderTexture(tex, _renderer, pix_x, pix_y, pix_w, pix_h, nullptr);
}

void vector_screen::present() {

  SDL_RenderPresent(_renderer);
}

void vector_screen::clear() {
  SDL_RenderClear(_renderer);
}
