#include "Game.h"
#include "TextureCreator.h"
#include "Map.h"
#include "GameObject.h"
#include "CollisionChecker.h"
#include "Food.h"
#include "TextObject.h"
#include "Ghost.h"

const int PLAYER_SPEED = 2;
int direction = 0;
int playerX = 400, playerY = 685, playerSourceX = 0;

int points = 0, lives = 3;

SDL_Renderer* Game::renderer = nullptr;
CollisionChecker collisionChecker;

Map* map;
Food* food;

TextObject* score;
TextObject* Lives;

GameObject* player;
Ghost* RedGhost, *BlueGhost, *PinkGhost, *OrangeGhost;

GameObject* lives_list[3];

Game::Game() { }

Game::~Game() { }

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

    TTF_Init();

    SDL_Surface *tmpSurface = IMG_Load("../assets/Icon.png");
    SDL_SetWindowIcon(window, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    for (int i = 0; i < 3; ++i) lives_list[i] = new GameObject("../assets/CharacterLife.png", 0, 0);

    player = new GameObject("../assets/Character.png", 0, 0);

    RedGhost = new Ghost(1);
    BlueGhost = new Ghost(2);
    PinkGhost = new Ghost(3);
    OrangeGhost = new Ghost(4);

    score = new TextObject("../fonts/ka1.ttf", 30, 0, 0);
    Lives = new TextObject("../fonts/ka1.ttf", 30, 0, 0);

    food = new Food();
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

    RedGhost->UpdateGhost(points);
    BlueGhost->UpdateGhost(points);
    PinkGhost->UpdateGhost(points);
    OrangeGhost->UpdateGhost(points);

    score->Update(50, 240, 540, 925, TextObject::score_toString(points));
    Lives->Update(50, 180, 40, 925, "Lifes: ");

    for (int i = 0; i < 3; ++i) lives_list[i]->Update(40, 40, 0, 0, 220 + i*50,932);

    // moving direction
    switch (direction) {
        case 1: if (!collisionChecker.RightWallCollision(playerX, playerY)) playerX += PLAYER_SPEED; break;
        case 2: if (!collisionChecker.DownWallCollision(playerX, playerY)) playerY += PLAYER_SPEED; break;
        case 3: if (!collisionChecker.LeftWallCollision(playerX, playerY)) playerX -= PLAYER_SPEED; break;
        case 4: if (!collisionChecker.UpWallCollision(playerX, playerY)) playerY -= PLAYER_SPEED; break;
        default: break;
    }

    // food detection
    int playerCellX = (playerX + 20) / 30, playerCellY = (playerY + 20) / 30;

    switch (direction) {
        case 1: {
            int any_food = food->get_food_by_coords(playerCellX + 1, playerCellY);
            if (any_food) {
                if ((playerX + 20) % 30 >= 25) {
                    food->eat_food(playerCellX + 1, playerCellY);
                    points++;
                }
            }
        } break;
        case 2: {
            int any_food = food->get_food_by_coords(playerCellX, playerCellY + 1);
            if (any_food) {
                if ((playerY + 20) % 30 >= 25) {
                    food->eat_food(playerCellX, playerCellY + 1);
                    points++;
                }
            }
        }
        case 3: {
            int any_food = food->get_food_by_coords(playerCellX - 1, playerCellY);
            if (any_food) {
                if ((playerX - 20) % 30 >= 25) {
                    food->eat_food(playerCellX - 1, playerCellY);
                    points++;
                }
            }
        }
        case 4: {
            int any_food = food->get_food_by_coords(playerCellX, playerCellY - 1);
            if (any_food) {
                if ((playerY - 20) % 30 >= 25) {
                    food->eat_food(playerCellX, playerCellY - 1);
                    points++;
                }
            }
        }
        default: break;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    map->drawMap();
    food->drawFood();

    player->Render();

    RedGhost->RenderGhost();
    BlueGhost->Render();
    PinkGhost->Render();
    OrangeGhost->Render();

    score->Render();
    Lives->Render();

    for (int i = 0; i < lives; ++i) lives_list[i]->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaning: OK" << '\n';
}