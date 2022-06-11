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
    ~Player() = default;

    void UpdatePlayer();
    int GhostCollisions(Ghost* ghosts[4], int ableToKill);
    int FoodCollisions();

    void ResetPlayer();

    void RenderPlayer();
    void SetDirection(int dir);
};


