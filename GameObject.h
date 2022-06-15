#pragma once
#include "Game.h"
#include "CollisionChecker.h"

class GameObject {
public:

    GameObject() = default;
    GameObject(const char* texturesheet);
    ~GameObject() = default;

    int GetX() const { return xPos; }
    int GetY() const { return yPos; }
    void Update(int sourceH, int sourceW, int sourceX, int sourceY, int destH, int destW, int destX, int destY);

    void Render();
protected:
    int xPos;
    int yPos;

    SDL_Texture *objectTexture;
    SDL_Rect sourceRectangle, destinationRectangle;
    CollisionChecker* collisionChecker;
};


