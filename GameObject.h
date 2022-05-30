#pragma once
#include "Game.h"

class GameObject {
public:

    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void Update(int sourceH, int sourceW, int sourceX, int sourceY);
    void Render();
private:
    int xPos;
    int yPos;

    SDL_Texture *objectTexture;
    SDL_Rect sourceRectangle, destinationRectangle;
};


