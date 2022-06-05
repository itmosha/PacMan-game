#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CollisionChecker.h"
#include "iostream"


class Game {
private:
    bool isRunning;
    SDL_Window *window;
    int points;
    int lives;
public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height);

    void TakeLife();
    void AddPoint();

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() const { return isRunning; };

    static SDL_Renderer* renderer;
    static int collisionChecker;
};


