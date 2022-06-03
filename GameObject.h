#pragma once
#include "Game.h"

class GameObject {
public:

    GameObject() = default;
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject() = default;

    void Update(int H, int W, int sourceX, int sourceY, int destX, int destY);

    void Render();
protected:
    int xPos;
    int yPos;

    SDL_Texture *objectTexture;
    SDL_Rect sourceRectangle, destinationRectangle;
};


