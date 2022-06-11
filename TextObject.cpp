#include "TextObject.h"
#include "TextureCreator.h"
#include "Game.h"

TextObject::TextObject(const char *font_path, int size) {
    font = TTF_OpenFont(font_path, size);
    color = {255, 255, 255};

    xPos = 0;
    yPos = 0;
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
    SDL_RenderCopy(Game::renderer, textTexture, nullptr, &destRect);
}

char* TextObject::score_toString(int scr) {

    char str_score[3] = {' ', ' ', ' '};
    int i = 2;

    char* string_text = new char[4];
    string_text[3] = '\0';

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
    string_text[0] = str_score[0]; string_text[1] = str_score[1]; string_text[2] = str_score[2];

    return string_text;
}

char TextObject::event_to_char(SDL_Event event, int playerNameSize) {
    char c = '!';
    switch (event.type) {
        case SDL_KEYDOWN: {
            switch (event.key.keysym.sym) {
                case SDLK_q: { c = 'Q'; } break;
                case SDLK_w: { c = 'W'; } break;
                case SDLK_e: { c = 'E'; } break;
                case SDLK_r: { c = 'R'; } break;
                case SDLK_t: { c = 'T'; } break;
                case SDLK_y: { c = 'Y'; } break;
                case SDLK_u: { c = 'U'; } break;
                case SDLK_i: { c = 'I'; } break;
                case SDLK_o: { c = 'O'; } break;
                case SDLK_p: { c = 'P'; } break;
                case SDLK_a: { c = 'A'; } break;
                case SDLK_s: { c = 'S'; } break;
                case SDLK_d: { c = 'D'; } break;
                case SDLK_f: { c = 'F'; } break;
                case SDLK_g: { c = 'G'; } break;
                case SDLK_h: { c = 'H'; } break;
                case SDLK_j: { c = 'J'; } break;
                case SDLK_k: { c = 'K'; } break;
                case SDLK_l: { c = 'L'; } break;
                case SDLK_z: { c = 'Z'; } break;
                case SDLK_x: { c = 'X'; } break;
                case SDLK_c: { c = 'C'; } break;
                case SDLK_v: { c = 'V'; } break;
                case SDLK_b: { c = 'B'; } break;
                case SDLK_n: { c = 'N'; } break;
                case SDLK_m: { c = 'M'; } break;
                default: break;
            }
        } break;
        default: break;
    }
    return c;
}