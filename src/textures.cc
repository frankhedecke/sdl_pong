#include "textures.h"

void logError(const std::string &msg){
  std::cout << ">>> " << msg << " error" << std::endl;
}

void logSDLError(const std::string &msg){
  std::cout << ">>> " << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* ren){

  SDL_Texture *texture = IMG_LoadTexture(ren, path.c_str());

  if (texture == nullptr){
    logSDLError("LoadTexture");
  }
  return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip) {

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != nullptr) {
    dst.w = clip->w;
    dst.h = clip->h;
  } else {
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
  }

  SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h, SDL_Rect* clip) {

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;

  SDL_RenderCopy(ren, tex, clip, &dst);
}
