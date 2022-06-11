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
Page* pages[8];
Ghost* ghosts[4];
Player* player;
Map* map;
Result* Res;

GameObject* nameBorder;
TextObject* playerNameBox;
TextObject* score;
TextObject* scoreIfLost;

Button* startGameButton;
Button* changePlayerButton;
Button* recordsButton;
Button* helpButton;
Button* exitMenuButton;

Button* continueButton;
Button* exitGameButton;

Button* replayWinButton;
Button* exitWinButton;

Button* ClearFileButton;
Button* PrintFileButton;
Button* ExitResultsButton;

GameObject* startGameButtonBorder;
GameObject* changePlayerButtonBorder;
GameObject* recordsButtonBorder;
GameObject* helpButtonBorder;
GameObject* exitMenuButtonBorder;

GameObject* continueButtonBorder;
GameObject* exitGameButtonBorder;

GameObject* replayWinButtonBorder;
GameObject* exitWinButtonBorder;

GameObject* ClearFileButtonBorder;
GameObject* PrintFileButtonBorder;
GameObject* ExitResultsButtonBorder;

GameObject* lives_list[3];
TextObject* scoreBoard[3][10];

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

    for (auto & i : lives_list) i = new GameObject("../assets/CharacterLife.png", 0, 0);

    player = new Player();
    for (int i = 0; i < 4; ++i) ghosts[i] = new Ghost(i+1);

    playerNameBox = new TextObject("../fonts/ka1.ttf", 30, 0, 0);
    nameBorder = new GameObject("../assets/NameBox.png", 0, 0);

    score = new TextObject("../fonts/ka1.ttf", 30, 0, 0);

    pages[0] = new Page("../assets/LoadingScreen.png");
    pages[1] = new Page("../assets/NameScreen.png");
    pages[2] = new Page(SmallPageSourceRect, SmallPageDestinationRect, "../assets/PauseScreen.png");
    pages[3] = new Page("../assets/MainMenuScreen.png");
    pages[4] = new Page("../assets/RecordsScreen.png");
    pages[5] = new Page("../assets/HelpScreen.png");
    pages[6] = new Page(SmallPageSourceRect, SmallPageDestinationRect, "../assets/WinScreen.png");
    pages[7] = new Page(SmallPageSourceRect, SmallPageDestinationRect, "../assets/LoseScreen.png");

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

    SDL_Rect rRClear{220, 700, 400, 80};
    ClearFileButton = new Button(rRClear);

    SDL_Rect rRPrint{220, 800, 400, 80};
    PrintFileButton = new Button(rRPrint);

    SDL_Rect rRExit{220, 900, 400, 80};
    ExitResultsButton = new Button(rRExit);

    scoreIfLost = new TextObject("../fonts/ka1.ttf", 50, 0, 0);

    continueButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    exitGameButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);

    replayWinButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    exitWinButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);

    startGameButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    changePlayerButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    recordsButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    helpButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    exitMenuButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);

    ClearFileButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    PrintFileButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);
    ExitResultsButtonBorder = new GameObject("../assets/MainMenuButtonBox.png", 0, 0);

    for (auto & i : scoreBoard) {
        for (auto & j : i) {
            j = new TextObject("../fonts/ka1.ttf", 30, 0, 0);
        }
    }
    map = new Map();
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
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if(ClearFileButton->checkIfPressed(event.button.x, event.button.y)) {
                        Res->ClearList();
                    }
                    if (PrintFileButton->checkIfPressed(event.button.x, event.button.y)) {
                        Res->PrintList();
                    }
                    if (ExitResultsButton->checkIfPressed(event.button.x, event.button.y)) {
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

    else if (win || lost) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (replayWinButton->checkIfPressed(event.button.x, event.button.y)) {
                        ResetGame();
                        player->ResetPlayer();
                        for (auto & ghost : ghosts) ghost->ResetGhost();

                        in_game = true;
                        win = false;
                        lost = false;
                    }
                    if (exitWinButton->checkIfPressed(event.button.x, event.button.y)) {
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
            } else {
                ableToKill = 0;
            }
        }

        for (auto &ghost: ghosts) ghost->UpdateGhost(points);

        for (int i = 0; i < 3; ++i) lives_list[i]->Update(40, 40, 0, 0, 40, 40, 220 + i*50,932);
        if (deathCooldown) deathCooldown--;
        if (ableToKill) ableToKill--;
    }
    score->Update(50, 100, 700, 925, TextObject::score_toString(points));
    scoreIfLost->Update(30, 60, 500, 365, TextObject::score_toString(points));
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

    ClearFileButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 700);
    PrintFileButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 800);
    ExitResultsButtonBorder->Update(80, 400, 0, 0, 80, 400, 220, 900);

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

        player->RenderPlayer();

        for (auto &ghost: ghosts) ghost->RenderGhost();

        score->Render();

        for (int i = 0; i < lives; ++i) lives_list[i]->Render();

        if (paused) {
            pages[2]->ShowPage();
            continueButtonBorder->Render();
            exitGameButtonBorder->Render();
        } else if (win) {
            pages[6]->ShowPage();
            replayWinButtonBorder->Render();
            exitWinButtonBorder->Render();
        } else if (lost) {
            pages[7]->ShowPage();
            replayWinButtonBorder->Render();
            exitWinButtonBorder->Render();
            scoreIfLost->Render();
        }
    }
    else if (firstScreenTime) {
        pages[0]->ShowPage();
    }
    else if (entering_name) {
        pages[1]->ShowPage();
        playerNameBox->Render();
        nameBorder->Render();
    }
    else if (in_main_menu) {
        pages[3]->ShowPage();
        startGameButtonBorder->Render();
        changePlayerButtonBorder->Render();
        recordsButtonBorder->Render();
        helpButtonBorder->Render();
        exitMenuButtonBorder->Render();
    }
    else if (in_records) {
        pages[4]->ShowPage();
        for (auto & i : scoreBoard) {
            for (auto & j : i) j->Render();
        }
        ClearFileButtonBorder->Render();
        PrintFileButtonBorder->Render();
        ExitResultsButtonBorder->Render();
    }
    else if (in_help_page) {
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

void Game::TakeLife() {lives--;}
void Game::AddPoint() {points++;}
Game::~Game() { }
