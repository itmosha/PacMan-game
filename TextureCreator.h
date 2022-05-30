#pragma once
#include "Game.h"

class TextureCreator {
public:
    static SDL_Texture* loadTexture(const char* filename);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};


