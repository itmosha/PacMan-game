#include "iostream"
#include "Game.h"


int main(int argc, char *argv[]) {
    Game *game = nullptr;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int frameStart;
    int frameTime;

    game = new Game();
    game->init("Pac-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 990);

    while (game->Running()) {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
    }
    game->Clean();

    return 0;
}
