#pragma once
#include "GameObject.h"
#include "Game.h"
#include "TextureCreator.h"
#include "CollisionChecker.h"
#include "Food.h"

class Player : public GameObject {
private:
    int direction;

public:
    Player();
    ~Player();

    bool UpdatePlayer();
    void RenderPlayer();
    void SetDirection(int dir);
};


