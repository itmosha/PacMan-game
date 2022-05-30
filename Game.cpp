#include "Game.h"
#include "TextureCreator.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
SDL_Renderer* Game::renderer = nullptr;
Map* map;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char *title, int xPos, int yPos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Initializing: OK" << '\n';

        window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
        if (window) std::cout << "Window: OK" << '\n';

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer: OK" << '\n';
        }
        isRunning = true;

    } else {
        isRunning = false;
    }

    player = new GameObject("../assets/Character.png", 400, 685);
    map = new Map();
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    player->Update(40, 40, 0, 0);
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();
    player->Render();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaning: OK" << '\n';
}