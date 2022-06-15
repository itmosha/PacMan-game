#pragma once
#include "Game.h"

class TextObject {
public:
    TextObject(const char* font, int size);
    ~TextObject() = default;

    void Update(int H, int W, int destX, int destY, const char* text);
    void Render();

    static char* ScoreToString(int scr);
    static char EventToChar(SDL_Event event);
private:
    int xPos;
    int yPos;

    SDL_Color color;
    TTF_Font *font;
    SDL_Texture* textTexture;
    SDL_Rect destRect;
};
