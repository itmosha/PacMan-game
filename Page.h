#pragma once
#include "Game.h"
#include "TextObject.h"
#include "TextureCreator.h"
#include "vector"

class Page {
private:
    SDL_Rect sourceRectangle{}, destinationRectangle{};
    SDL_Texture* pageTexture;

public:
    Page(SDL_Rect src, SDL_Rect dest, const char* path);
    ~Page();

    void ShowPage();
};


