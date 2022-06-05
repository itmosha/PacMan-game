#pragma once
#include "GameObject.h"
#include "Game.h"
#include "TextureCreator.h"
#include "CollisionChecker.h"
#include "Food.h"
#include "Ghost.h"

class Player : public GameObject {
private:
    int direction;
    CollisionChecker* collisionCheckerPlayer;

public:
    Player();
    ~Player();

    void UpdatePlayer();
    bool GhostCollisions(Ghost* ghosts[4]);
    bool FoodCollisions();

    void RenderPlayer();
    void SetDirection(int dir);
};


