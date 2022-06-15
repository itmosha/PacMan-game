#pragma once
#include "Game.h"

class Map {
public:
    Map();
    ~Map() = default;

    bool GetMapElement(int row, int column);
    void LoadMap();
    void DrawMap();

private:
    SDL_Rect source, destination;

    int map[33][28];
};


