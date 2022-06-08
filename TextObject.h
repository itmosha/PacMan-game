#pragma once
#include "Game.h"

class TextObject {
public:
    TextObject(const char* font, int size, int x, int y);
    ~TextObject();

    void Update(int H, int W, int destX, int destY, const char* text);
    void Render();

    static char* score_toString(int scr);
    static char event_to_char(SDL_Event event, int playerNameSize);
private:
    int xPos;
    int yPos;

    SDL_Color color;
    TTF_Font *font;
    SDL_Texture* textTexture;
    SDL_Rect destRect;
};
