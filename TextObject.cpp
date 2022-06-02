#include "TextObject.h"
#include "TextureCreator.h"
#include "Game.h"

TextObject::TextObject(const char *font_path, int size, int x, int y) {
    font = TTF_OpenFont(font_path, size);
    color = {255, 255, 255};

    xPos = x;
    yPos = y;
}

void TextObject::Update(int H, int W, int destX, int destY, const char* text) {

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);

    textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);

    SDL_FreeSurface(textSurface);

    destRect.w = W;
    destRect.h = H;
    destRect.x = destX;
    destRect.y = destY;
}

void TextObject::Render() {
    SDL_RenderCopy(Game::renderer, textTexture, NULL, &destRect);
}

char* TextObject::score_toString(int scr) {

    char str_score[3] = {' ', ' ', ' '};
    int i = 2;

    char* string_text = new char[10];
    string_text[0] = 's'; string_text[1] = 'c'; string_text[2] = 'o'; string_text[3] = 'r'; string_text[4] = 'e';
    string_text[5] = ':'; string_text[6] = ' ';

    if (scr == 0) {
        str_score[2] = '0';
    }
    else {
        while (scr > 0) {
            char c = scr % 10 + '0';
            str_score[i] = c;

            i--;
            scr /= 10;
        }
    }
    string_text[7] = str_score[0]; string_text[8] = str_score[1]; string_text[9] = str_score[2];

    return string_text;
}
