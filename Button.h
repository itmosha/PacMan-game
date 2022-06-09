#pragma once
#include "Game.h"

class Button {
private:
    SDL_Rect buttonRect;
public:
    Button(SDL_Rect bRect);
    bool checkIfPressed(int mouseX, int mouseY);

    ~Button();
};

