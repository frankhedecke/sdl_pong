#pragma once

#include <string>
#include <SDL.h>

#define uint uint16_t

class vector_screen {

  private:
    uint _res_x;
    uint _res_y;
    // delete dims
    float _dim_x;
    float _dim_y;
    SDL_Renderer* _renderer;

  public:
    vector_screen(SDL_Window* window, float dim_x, float dim_y);
    ~vector_screen();
    void update_res(uint res_x,uint res_y);
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
