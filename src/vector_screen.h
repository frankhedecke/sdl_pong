#pragma once

#include <string>
#include <SDL.h>

#define uint uint16_t

class vector_screen {

  private:
    // fullscreen
    uint _fs_res_x;
    uint _fs_res_y;
    uint _fs_res;
    uint _fs_offset_x;
    uint _fs_offset_y;
    // window mode
    uint _res_x;
    uint _res_y;
    uint _res;
    uint _offset_x;
    uint _offset_y;
    // window mode old
    uint _windowed_base_res;
    uint _windowed_bup_res;
    // other
    SDL_Renderer* _renderer;
    SDL_Window* _window;
    // TODO use _window to check if fullscreen is set
    bool _is_fullscreen;

  public:
    vector_screen(SDL_Window* window, uint res_x = 640);
    ~vector_screen();
    void update_res();
    void toggle_fullscreen();
    SDL_Texture* load_Texture(const std::string &path);
    SDL_Texture* loadText(const std::string &text, int font_size);
    void render_Texture(float x, float y, float dim_x, float dim_y, SDL_Texture* tex);
    void present();
    void clear();
    // TODO
    // rename methods with _
    // rename into Vector_screen
    // void renderTextureCentered(SDL_Texture* tex, float x, float y);
    // SDL_Texture* clipTexture(SDL_Texture* tex, int x, int y);
};
