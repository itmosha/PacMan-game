#pragma once
#include "Game.h"

class Map {
public:
    Map();
    ~Map() = default;

    bool get_map_element(int row, int column);
    void loadMap();
    void drawMap();

private:
    SDL_Rect source, destination;

    int map[33][28];
};


