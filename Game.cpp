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
#include "Result.h"

const SDL_Rect SmallPageSourceRect{0,0,640,390}, SmallPageDestinationRect{100,300,640,390};
SDL_Renderer* Game::renderer = nullptr;

char* playerName = new char[16];

Player* player;
Map* map;
Result* Res;

Page* pages[8];
Ghost* ghosts[4];
GameObject* lives_list[3];
TextObject* scoreBoard[3][10];

GameObject* mainMenuButtonBorders[5];
Button* mainMenuButtons[5];

GameObject* pauseButtonBorders[2];
Button* pauseButtons[2];

GameObject* replayExitButtonBorders[2];
Button* replayExitButtons[2];

GameObject* recordsButtonBorders[3];
Button* recordsButtons[3];

GameObject* nameBorder;
TextObject* playerNameBar;
TextObject* score;
TextObject* scoreIfLost;

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

    } else isRunning = false;

    if (TTF_Init() == 0) {
        std::cout << "TTF: OK" << '\n';
    } else isRunning = false;

    SDL_Surface *tmpSurface = IMG_Load("../assets/Icon.png");
    SDL_SetWindowIcon(window, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    Res = new Result();
    map = new Map();
    player = new Player();

    playerNameBar = new TextObject("../fonts/ka1.ttf", 30);
    nameBorder = new GameObject("../assets/NameBox.png");
    score = new TextObject("../fonts/ka1.ttf", 30);
    scoreIfLost = new TextObject("../fonts/ka1.ttf", 30);

    pages[0] = new Page("../assets/LoadingScreen.png");
    pages[1] = new Page("../assets/NameScreen.png");
    pages[2] = new Page(SmallPageSourceRect, SmallPageDestinationRect, "../assets/PauseScreen.png");
    pages[3] = new Page("../assets/MainMenuScreen.png");
    pages[4] = new Page("../assets/RecordsScreen.png");
    pages[5] = new Page("../assets/HelpScreen.png");
    pages[6] = new Page(SmallPageSourceRect, SmallPageDestinationRect, "../assets/WinScreen.png");
    pages[7] = new Page(SmallPageSourceRect, SmallPageDestinationRect, "../assets/LoseScreen.png");

    for (auto & mainMenuButtonBorder : mainMenuButtonBorders) mainMenuButtonBorder = new GameObject("../assets/ButtonBorder.png");
    for (auto & pauseButtonBorder : pauseButtonBorders) pauseButtonBorder = new GameObject("../assets/ButtonBorder.png");
    for (auto & replayExitButtonBorder : replayExitButtonBorders) replayExitButtonBorder = new GameObject("../assets/ButtonBorder.png");
    for (auto & recordsButtonBorder : recordsButtonBorders) recordsButtonBorder = new GameObject("../assets/ButtonBorder.png");
    for (auto & i : lives_list) i = new GameObject("../assets/CharacterLife.png");
    for (int i = 0; i < 4; ++i) ghosts[i] = new Ghost(i+1);

    for (int i = 0; i < 5; ++i) {
        SDL_Rect buttonRect{100, 300 + i*100, 400, 80};
        mainMenuButtons[i] = new Button(buttonRect);
    }

    for (int i = 0; i < 2; ++i) {
        SDL_Rect buttonRect{220, 400 + i*100, 400, 80};
        pauseButtons[i] = new Button(buttonRect);
        replayExitButtons[i] = new Button(buttonRect);
    }

    for (int i = 0; i < 3; ++i) {
        SDL_Rect buttonRect{220, 700 + i*100, 400, 80};
        recordsButtons[i] = new Button(buttonRect);
    }

    for (auto & i : scoreBoard) {
        for (auto & j : i) {
            j = new TextObject("../fonts/ka1.ttf", 30);
        }
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            Res->SaveToFile();
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
                    if (mainMenuButtons[0]->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        in_game = true;
                    }
                    if (mainMenuButtons[1]->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        entering_name = true;
                    }
                    if (mainMenuButtons[2]->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        in_records = true;
                    }
                    if (mainMenuButtons[3]->checkIfPressed(event.button.x, event.button.y)) {
                        in_main_menu = false;
                        in_help_page = true;
                    }
                    if (mainMenuButtons[4]->checkIfPressed(event.button.x, event.button.y)) {
                        Res->SaveToFile();

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
                            player->SetDirection(1);
                            break;
                        case SDLK_s:
                            player->SetDirection(2);
                            break;
                        case SDLK_a:
                            player->SetDirection(3);
                            break;
                        case SDLK_w:
                            player->SetDirection(4);
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
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if(recordsButtons[0]->checkIfPressed(event.button.x, event.button.y)) {
                        Res->ClearList();
                    }
                    if (recordsButtons[1]->checkIfPressed(event.button.x, event.button.y)) {
                        Res->PrintList();
                    }
                    if (recordsButtons[2]->checkIfPressed(event.button.x, event.button.y)) {
                        in_records = false;
                        in_main_menu = true;
                    }
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
                    if (pauseButtons[0]->checkIfPressed(event.button.x, event.button.y)) {
                        in_game = true;
                        paused = false;
                    }
                    if (pauseButtons[1]->checkIfPressed(event.button.x, event.button.y)) {
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

    else if (win || lost) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (replayExitButtons[0]->checkIfPressed(event.button.x, event.button.y)) {
                        ResetGame();
                        player->ResetPlayer();
                        for (auto & ghost : ghosts) ghost->ResetGhost();

                        in_game = true;
                        win = false;
                        lost = false;
                    }
                    if (replayExitButtons[1]->checkIfPressed(event.button.x, event.button.y)) {
                        ResetGame();
                        player->ResetPlayer();
                        for (auto & ghost : ghosts) ghost->ResetGhost();

                        in_main_menu = true;
                        win = false;
                        lost = false;

                    }
                }
            } break;
        }
    }

    if (points == 244) {
        win = true;
        in_game = false;
        if (!written) {
            Res->AddResult(playerName, points);
            written = true;
        }
    }

    if (lives == 0) {
        lost = true;
        in_game = false;

        if (!written) {
            Res->AddResult(playerName, points);
            written = true;
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
            } else ableToKill = 0;
        }

        for (auto &ghost: ghosts) ghost->UpdateGhost(points);

        for (int i = 0; i < 3; ++i) lives_list[i]->Update(40, 40, 0, 0, 40, 40, 220 + i*50,932);
        if (deathCooldown) deathCooldown--;
        if (ableToKill) ableToKill--;
    }
    score->Update(50, 100, 700, 925, TextObject::score_toString(points));
    scoreIfLost->Update(30, 60, 500, 365, TextObject::score_toString(points));
    playerNameBar->Update(60, nameBoxWidth, 420-nameBoxWidth/2, 465, playerName);
    nameBorder->Update(80, 660, 0, 0, 80, 670, 82, 451);
    for (int i = 0; i < 5; ++i) mainMenuButtonBorders[i]->Update(80, 400, 0, 0, 80, 400, 220, 300 + i*100);
    for (int i = 0; i < 2; ++i) pauseButtonBorders[i]->Update(80, 400, 0, 0, 80, 400, 220, 420 + i*100);
    for (int i = 0; i < 2; ++i) replayExitButtonBorders[i]->Update(80, 400, 0, 0, 80, 400, 220, 420 + i*100);
    for (int i = 0; i < 3; ++i) recordsButtonBorders[i]->Update(80, 400, 0, 0, 80, 400, 220, 700 + i*100);

    for (int i = 0; i < Res->records.size(); ++i) scoreBoard[0][i]->Update(30, 60, 20, 150+i*50, TextObject::score_toString(i+1));
    for (int i = 0; i < Res->records.size(); ++i) scoreBoard[1][i]->Update(30, 90, 150, 150+i*50, TextObject::score_toString(Res->records[i].pts));
    for (int i = 0; i < Res->records.size(); ++i) scoreBoard[2][i]->Update(30, strlen(Res->records[i].name)*30, 300, 150 + i*50, Res->records[i].name);

    if (firstScreenTime) firstScreenTime--;
    if (playerNameSize == 0) entering_name = true;
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (in_game || paused || win || lost) {
        map->drawMap();
        score->Render();
        for (int i = 0; i < lives; ++i) lives_list[i]->Render();

        for (auto &ghost: ghosts) ghost->RenderGhost();
        player->RenderPlayer();

        if (paused) {
            pages[2]->ShowPage();
            for (auto & pauseButtonBorder : pauseButtonBorders) pauseButtonBorder->Render();
        } else if (win) {
            pages[6]->ShowPage();
            for (auto & replayExitButtonBorder : replayExitButtonBorders) replayExitButtonBorder->Render();
        } else if (lost) {
            pages[7]->ShowPage();
            for (auto & replayExitButtonBorder : replayExitButtonBorders) replayExitButtonBorder->Render();
            scoreIfLost->Render();
        }
    } else if (firstScreenTime) {
        pages[0]->ShowPage();
    } else if (entering_name) {
        pages[1]->ShowPage();
        playerNameBar->Render();
        nameBorder->Render();
    } else if (in_main_menu) {
        pages[3]->ShowPage();
        for (auto & mainMenuButtonBorder : mainMenuButtonBorders) mainMenuButtonBorder->Render();
    } else if (in_records) {
        pages[4]->ShowPage();
        for (auto & i : scoreBoard) for (int j = 0; j < Res->records.size(); ++j) i[j]->Render();
        for (auto & recordsButtonBorder : recordsButtonBorders) recordsButtonBorder->Render();
    } else if (in_help_page) {
        pages[5]->ShowPage();
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
    in_game = false;
    entering_name = false;
    in_main_menu = false;
    paused = false;
    in_records = false;
    in_help_page = false;
    win = false;
    lost = false;
    written = false;

    points = 0;
    lives = 3;
    deathCooldown = 0;
    ableToKill = 0;
    firstScreenTime = 240;
    playerNameSize = 0;
    nameBoxWidth = 0;

    playerName = new char[16];
}

void Game::ResetGame() {
    written = false;
    points = 0;
    lives = 3;
    deathCooldown = 0;
    ableToKill = 0;
}

void Game::TakeLife() { lives--; }
void Game::AddPoint() { points++; }
Game::~Game() { }
