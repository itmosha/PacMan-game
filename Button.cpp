#include "Button.h"

Button::Button(SDL_Rect bRect) {
    buttonRect.x = bRect.x;
    buttonRect.y = bRect.y;
    buttonRect.h = bRect.h;
    buttonRect.w = bRect.w;
}

bool Button::CheckIfPressed(int mouseX, int mouseY) {
    if (mouseX >= buttonRect.x && mouseX <= (buttonRect.x + buttonRect.w) &&
        mouseY >= buttonRect.y && mouseY <= (buttonRect.y + buttonRect.h)) return true;
    return false;
}