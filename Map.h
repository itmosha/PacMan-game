#pragma once
#include "Game.h"

class Map {
public:
    Map();
    ~Map();

    void loadMap(bool arr[33][28]);
    void drawMap();

private:
    SDL_Rect source, destination;
    SDL_Texture* floor;
    SDL_Texture* walls;

    int map[33][28];
};


