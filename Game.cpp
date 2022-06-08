#include "Game.h"
#include "TextureCreator.h"
#include "Map.h"
#include "GameObject.h"
#include "CollisionChecker.h"
#include "Food.h"
#include "TextObject.h"
#include "Ghost.h"
#include "Player.h"
#include "Page.h"

char* playerName = new char[16];

int deathCooldown = 0;
int ableToKill = 0;
int firstScreenTime = 120;

bool in_game = false;
bool entering_name = false;
bool in_main_menu = false;
bool paused = false;

int playerNameSize = 0;
int nameBoxWidth = 0;

SDL_Renderer* Game::renderer = nullptr;
Map* map;

GameObject* nameBorder;
TextObject* playerNameBox;
TextObject* score;
TextObject* Lives;

Player* player;
Ghost* ghosts[4];

Page* loadingScreen;
Page* nameScreen;
Page* pauseScreen;

GameObject* lives_list[3];

Game::Game() { points = 0; lives = 3; }
void Game::TakeLife() {lives--;}
void Game::AddPoint() {points++;}
Game::~Game() { }

void Game::init(const char *title, int xPos, int yPos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Initializing: OK" << '\n';

        window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
        if (window) std::cout << "Window: OK" << '\n';

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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


    for (auto & i : lives_list) i = new GameObject("../assets/CharacterLife.png", 0, 0);

    player = new Player();
    for (int i = 0; i < 4; ++i) ghosts[i] = new Ghost(i+1);

    playerNameBox = new TextObject("../fonts/ka1.ttf", 30, 0, 0);

    score = new TextObject("../fonts/ka1.ttf", 30, 0, 0);
    Lives = new TextObject("../fonts/ka1.ttf", 30, 0, 0);

    loadingScreen = new Page("../assets/LoadingScreen.png");
    nameScreen = new Page("../assets/NameScreen.png");
    nameBorder = new GameObject("../assets/NameBox.png", 0, 0);
    pauseScreen = new Page("../assets/NameScreen.png");

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
                case SDLK_d: if (in_game) player->SetDirection(1); break;
                case SDLK_s: if (in_game) player->SetDirection(2); break;
                case SDLK_a: if (in_game) player->SetDirection(3); break;
                case SDLK_w: if (in_game) player->SetDirection(4); break;
                case SDLK_ESCAPE: {
                    if (in_game) {
                        in_game = false;
                        paused = true;
                        }
                    else {
                        in_game = true;
                        paused = false;
                        }
                    } break;
                }
            }
        default:
            break;
    }
    if (entering_name) {

        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_RETURN: {
                        entering_name = false;
                        in_main_menu = true;
                    } break;
                    case SDLK_BACKSPACE: {
                        if (playerNameSize > 0) {
                            playerName[playerNameSize - 1] = '\0';
                            playerNameSize--;
                            nameBoxWidth -= 40;
                        }
                    } break;
                    default: {
                        if (playerNameSize < 16) {
                            char c = TextObject::event_to_char(event, playerNameSize);
                            if (c != '!') {
                                playerName[playerNameSize] = c;
                                playerNameSize++;
                                nameBoxWidth += 40;
                            }
                        }
                    } break;
                }
            } break;
            default: break;
        }
    }
}

void Game::update() {
    if (in_game) {
        player->UpdatePlayer();

        int food_eaten = player->FoodCollisions();
        if (food_eaten) {
            points++;
            if (food_eaten == 2) ableToKill = 300;
        }

        int killEvent = player->GhostCollisions(ghosts, ableToKill);

        if (killEvent) {
            if (killEvent == 1 && !deathCooldown) {
                lives--;
                deathCooldown = 180;
            } else {
                ableToKill = 0;
            }
        }

        for (auto &ghost: ghosts) ghost->UpdateGhost(points);

        for (int i = 0; i < 3; ++i) lives_list[i]->Update(40, 40, 0, 0, 40, 40, 220 + i*50,932);
        if (deathCooldown) deathCooldown--;
        if (ableToKill) ableToKill--;
    }
    score->Update(50, 240, 540, 925, TextObject::score_toString(points));
    Lives->Update(50, 180, 40, 925, "LIFES: ");
    playerNameBox->Update(60, nameBoxWidth, 420-nameBoxWidth/2, 465, playerName);
    nameBorder->Update(80, 660, 0, 0, 80, 670, 82, 451);

    if (firstScreenTime) {
        firstScreenTime--;
    }

    if (playerNameSize == 0) entering_name = true;
    else { in_main_menu = true; }

    in_main_menu = false; // FIX!!!

    if (!entering_name && !in_main_menu && !paused) in_game = true;

}

void Game::render() {
    SDL_RenderClear(renderer);

    if (in_game) {
        map->drawMap();

        player->RenderPlayer();

        for (auto &ghost: ghosts) ghost->RenderGhost();

        score->Render();
        Lives->Render();

        for (int i = 0; i < lives; ++i) lives_list[i]->Render();
    }
    if (firstScreenTime) {
        loadingScreen->ShowPage();
    }
    else if (entering_name) {
        nameScreen->ShowPage();
        playerNameBox->Render();
        nameBorder->Render();
    }
    else if (paused) {
        pauseScreen->ShowPage();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaning: OK" << '\n';
}