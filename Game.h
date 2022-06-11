#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CollisionChecker.h"
#include "iostream"

class Game {
private:
    bool isRunning;

    bool in_game;
    bool entering_name;
    bool in_main_menu;
    bool paused;
    bool in_records;
    bool in_help_page;
    bool win;
    bool lost;
    bool written;

    int points;
    int lives;
    int deathCooldown;
    int ableToKill;
    int firstScreenTime;
    int playerNameSize;
    int nameBoxWidth;

    SDL_Window *window;

public:
    Game();
    ~Game() = default;

    void init(const char* title, int xPos, int yPos, int width, int height);

    void TakeLife();
    void AddPoint();
    void handleEvents();
    void update();
    void render();
    void clean();

    void ResetGame();

    bool running() const { return isRunning; };

    static SDL_Renderer* renderer;
    static int collisionChecker;
};


