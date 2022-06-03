#pragma once
#include "GameObject.h"
#include "Game.h"

class Ghost : public GameObject {
private:
    bool is_active;
    int direction;
    int type; // 1 - RED, 2 - BLUE, 3 - PINK, 4 - ORANGE
public:
    explicit Ghost(int ghost_type);
    ~Ghost() = default;

    void UpdateGhost(int points);
    void RenderGhost();
};
