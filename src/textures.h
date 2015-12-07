#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

void logError(const std::string &msg);

void logSDLError(const std::string &msg);

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer* ren);

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr);

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h, SDL_Rect* clip = nullptr);
