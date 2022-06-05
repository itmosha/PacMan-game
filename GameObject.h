#pragma once
#include "Game.h"
//#include "SDL.h"
//#include "SDL_image.h"
#include "CollisionChecker.h"

class GameObject {
public:

    GameObject() = default;
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject() = default;

    int GetX() { return xPos; }
    int GetY() { return yPos; }
    void Update(int H, int W, int sourceX, int sourceY, int destX, int destY);

    void Render();
protected:
    int xPos;
    int yPos;

    SDL_Texture *objectTexture;
    SDL_Rect sourceRectangle, destinationRectangle;
    CollisionChecker* collisionChecker;
};


