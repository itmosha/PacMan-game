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

Page::Page(const char* path) {
    pageTexture = TextureCreator::loadTexture(path);

    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = 840;
    sourceRectangle.h = 990;

    destinationRectangle.x = 0;
    destinationRectangle.y = 0;
    destinationRectangle.w = 840;
    destinationRectangle.h = 990;
}

void Page::ShowPage() {
    SDL_RenderCopy(Game::renderer, pageTexture, &sourceRectangle, &destinationRectangle);
}