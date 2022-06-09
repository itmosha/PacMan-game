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
#include "Button.h"

char* playerName = new char[16];


bool in_game = false;
bool entering_name = false;
bool in_main_menu = false;
bool paused = false;
bool in_records = false;
bool in_help_page = false;
bool win = false;

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
Page* mainMenu;
Page* recordsScreen;
Page* helpScreen;
Page* winScreen;

Button* startGameButton;
Button* changePlayerButton;
Button* recordsButton;
Button* helpButton;
Button* exitMenuButton;

Button* continueButton;
Button* exitGameButton;

Button* replayWinButton;
Button* exitWinButton;

GameObject* startGameButtonBorder;
GameObject* changePlayerButtonBorder;
GameObject* recordsButtonBorder;
GameObject* helpButtonBorder;
GameObject* exitMenuButtonBorder;

GameObject* continueButtonBorder;
GameObject* exitGameButtonBorder;

GameObject* replayWinButtonBorder;
GameObject* exitWinButtonBorder;

GameObject* lives_list[3];


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
    nameBorder = new GameObject("../assets/NameBox.png", 0, 0);

    score = new TextObject("../fonts/ka1.ttf", 30, 0, 0);
    Lives = new TextObject("../fonts/ka1.ttf", 30, 0, 0);

    loadingScreen = new Page("../assets/LoadingScreen.png");
    nameScreen = new Page("../assets/NameScreen.png");

    SDL_Rect sPause{0, 0, 640, 390}, dPause{100, 300, 640, 390};
    pauseScreen = new Page(sPause, dPause, "../assets/PauseScreen.png");
    winScreen = new Page(sPause, dPause, "../assets/WinScreen.png");

    mainMenu = new Page("../assets/MainMenu.png");
    recordsScreen = new Page("../assets/RecordsScreen.png");
    helpScreen = new Page("../assets/HelpScreen.png");

    SDL_Rect rStart{100, 300, 400, 80};
    startGameButton = new Button(rStart);

    SDL_Rect rChangePlayer{100, 400, 400, 80};
    changePlayerButton = new Button(rChangePlayer);

    SDL_Rect rRecords{100, 500, 400, 80};
    recordsButton = new Button(rRecords);

    SDL_Rect rHelp{100, 600, 400, 80};
    helpButton = new Button(rHelp);

    SDL_Rect rExit{100, 700, 400, 80};
    exitMenuButton = new Button(rExit);

    SDL_Rect rContinue{220, 400, 400, 80};
    continueButton = new Button(rContinue);

    SDL_Rect rGExit{220, 500, 400, 80};
    exitGameButton = new Button(rGExit);

    SDL_Rect rWReplay{220, 400, 400, 80};
    replayWinButton = new Button(rWReplay);

    SDL_Rect rWExit{220, 500, 400, 80};
    exitWinButton = new Button(rWExit);

    continueButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    exitGameButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);

    replayWinButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    exitWinButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);

    startGameButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    changePlayerButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    recordsButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    helpButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    exitMenuButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
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

    else if (in_main_menu) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (startGameButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        in_game = true;
                    }
                    if (changePlayerButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        entering_name = true;
                    }
                    if (recordsButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        in_records = true;
                    }
                    if (helpButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        in_help_page = true;
                    }
                    if (exitMenuButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        isRunning = false;
                    }
                }
            } break;
        }
    }

    else if (in_game) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {

                        case SDLK_d:
                            if (in_game) player->SetDirection(1);
                            break;
                        case SDLK_s:
                            if (in_game) player->SetDirection(2);
                            break;
                        case SDLK_a:
                            if (in_game) player->SetDirection(3);
                            break;
                        case SDLK_w:
                            if (in_game) player->SetDirection(4);
                            break;
                        case SDLK_ESCAPE: {
                            in_game = false;
                            paused = true;
                        } break;
                    }
                } break;
            }
        }
    
    else if (in_records) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        in_records = false;
                        in_main_menu = true;
                        paused = false;
                    } break;
                }
            } break;
        }
    }
    
    else if (paused) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                            paused = false;
                            in_game = true;
                    }
                }
            } break;
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (continueButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_game = true;
                        paused = false;
                    }
                    if (exitGameButton->checkIfPressed(event.button.x, event.button.y)) {
                        in_game = false;
                        in_main_menu = true;
                        paused = false;
                        ResetGame();
                        player->ResetPlayer();
                        for (auto & ghost : ghosts) ghost->ResetGhost();
                    }
                }
            } break;
        }
    }

    else if (in_help_page) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        in_help_page = false;
                        in_main_menu = true;
                    } break;
                }
            } break;
        }
    }

    else if (win) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (replayWinButton->checkIfPressed(event.button.x, event.button.y)) {
                        ResetGame();
                        player->ResetPlayer();
                        for (auto & ghost : ghosts) ghost->ResetGhost();

                        in_game = true;
                        win = false;
                    }
                    if (exitWinButton->checkIfPressed(event.button.x, event.button.y)) {
                        ResetGame();
                        player->ResetPlayer();
                        for (auto & ghost : ghosts) ghost->ResetGhost();

                        in_main_menu = true;
                        win = false;
                    }
                }
            } break;
        }
    }

    if (points == 244) {
        win = true;
        in_game = false;
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

    continueButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 420);
    exitGameButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 520);

    startGameButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 300);
    changePlayerButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 400);
    recordsButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 500);
    helpButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 600);
    exitMenuButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 700);

    replayWinButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 420);
    exitWinButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 520);

    if (firstScreenTime) firstScreenTime--;
    if (playerNameSize == 0) entering_name = true;
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (in_game || paused || win) {
        map->drawMap();

        player->RenderPlayer();

        for (auto &ghost: ghosts) ghost->RenderGhost();

        score->Render();
        Lives->Render();

        for (int i = 0; i < lives; ++i) lives_list[i]->Render();

        if (paused) {
            pauseScreen->ShowPage();
            continueButtonBorder->Render();
            exitGameButtonBorder->Render();
        } else if (win) {
            winScreen->ShowPage();
            replayWinButtonBorder->Render();
            exitWinButtonBorder->Render();
        }
    }
    else if (firstScreenTime) {
        loadingScreen->ShowPage();
    }
    else if (entering_name) {
        nameScreen->ShowPage();
        playerNameBox->Render();
        nameBorder->Render();
    }
    else if (in_main_menu) {
        mainMenu->ShowPage();
        startGameButtonBorder->Render();
        changePlayerButtonBorder->Render();
        recordsButtonBorder->Render();
        helpButtonBorder->Render();
        exitMenuButtonBorder->Render();
    }
    else if (in_records) {
        recordsScreen->ShowPage();
    }
    else if (in_help_page) {
        helpScreen->ShowPage();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Cleaning: OK" << '\n';
}

Game::Game() {
    points = 0;
    lives = 3;
    deathCooldown = 0;
    ableToKill = 0;
    firstScreenTime = 5;
}

void Game::ResetGame() {
    points = 0;
    lives = 3;
    deathCooldown = 0;
    ableToKill = 0;
}

void Game::TakeLife() {lives--;}
void Game::AddPoint() {points++;}
Game::~Game() { }
