#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "iostream"

class Game {
private:
    bool isRunning;
    SDL_Window *window;
public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; };

    static SDL_Renderer* renderer;
};


