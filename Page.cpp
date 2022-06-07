#include "Page.h"

Page::Page(SDL_Rect src, SDL_Rect dest, const char* path) {

    pageTexture = TextureCreator::loadTexture(path);

    sourceRectangle.x = src.x;
    sourceRectangle.y = src.y;
    sourceRectangle.w = src.w;
    sourceRectangle.h = src.h;

    destinationRectangle.x = dest.x;
    destinationRectangle.y = dest.y;
    destinationRectangle.w = dest.w;
    destinationRectangle.h = dest.h;
}


void Page::ShowPage() {
    SDL_RenderCopy(Game::renderer, pageTexture, &sourceRectangle, &destinationRectangle);
}