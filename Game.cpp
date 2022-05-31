#include "Game.h"
#include "TextureCreator.h"
#include "Map.h"
#include "GameObject.h"

const int PLAYER_SPEED = 2;
int direction = 0;
int playerX = 400, playerY = 685, playerSourceX = 0;

SDL_Renderer* Game::renderer = nullptr;
Map* map;
GameObject* player;

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
        case SDL_KEYDOWN: {
            switch (event.key.keysym.sym) {
                case SDLK_d: direction = 1; playerSourceX = 40; break;
                case SDLK_s: direction = 2; playerSourceX = 80; break;
                case SDLK_a: direction = 3; playerSourceX = 120; break;
                case SDLK_w: direction = 4; playerSourceX = 160; break;
            }
        }
        default:
            break;
    }
}

void Game::update() {
    player->Update(40, 40, playerSourceX, 0, playerX, playerY);
    switch (direction) {
        case 1: playerX += PLAYER_SPEED; break;
        case 2: playerY += PLAYER_SPEED; break;
        case 3: playerX -= PLAYER_SPEED; break;
        case 4: playerY -= PLAYER_SPEED; break;
        default: break;
    }
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