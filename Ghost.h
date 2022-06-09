#pragma once
#include "GameObject.h"
#include "Game.h"
//#include "CollisionChecker.h"

const int GHOST_SPEED = 1;

class Ghost : public GameObject {
private:
    bool killed;
    bool is_active;
    int direction;
    int type; // 1 - RED, 2 - BLUE, 3 - PINK, 4 - ORANGE
    CollisionChecker* collisionCheckerGhost;
public:
    explicit Ghost(int ghost_type);
    ~Ghost() = default;

    bool CheckActive();
    void UnableGhost();
    void Kill();

    void ResetGhost();

    void UpdateGhost(int points);
    void RenderGhost();
};
