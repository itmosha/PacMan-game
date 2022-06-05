#include "Player.h"
const int PLAYER_SPEED = 2;

Food* food;

Player::Player() {
    objectTexture = TextureCreator::loadTexture("../assets/Character.png");
    collisionCheckerPlayer = new CollisionChecker();
    food = new Food();

    xPos = 400;
    yPos = 685;
    direction = 0;
}

void Player::SetDirection(int dir) { direction = dir; }

void Player::UpdatePlayer() {

    int sourceX;
    switch (direction) {
        case 0:
            sourceX = 0;
            break;
        case 1:
            sourceX = 40;
            break;
        case 2:
            sourceX = 80;
            break;
        case 3:
            sourceX = 120;
            break;
        case 4:
            sourceX = 160;
            break;
    }

    sourceRectangle.h = 40;
    sourceRectangle.w = 40;
    sourceRectangle.x = sourceX;
    sourceRectangle.y = 0;

    destinationRectangle.h = 40;
    destinationRectangle.w = 40;
    destinationRectangle.x = xPos;
    destinationRectangle.y = yPos;

    switch (direction) {
        case 1:
            if (!collisionCheckerPlayer->RightWallCollision(xPos, yPos)) xPos += PLAYER_SPEED;
            break;
        case 2:
            if (!collisionCheckerPlayer->DownWallCollision(xPos, yPos)) yPos += PLAYER_SPEED;
            break;
        case 3:
            if (!collisionCheckerPlayer->LeftWallCollision(xPos, yPos)) xPos -= PLAYER_SPEED;
            break;
        case 4:
            if (!collisionCheckerPlayer->UpWallCollision(xPos, yPos)) yPos -= PLAYER_SPEED;
            break;
        default:
            break;
    }
}

bool Player::FoodCollisions() {
    int playerCellX = (xPos + 20) / 30, playerCellY = (yPos + 20)/30;
    switch (direction) {
        case 1: {
            int any_food = food->get_food_by_coords(playerCellX + 1, playerCellY);
            if (any_food) {
                if ((xPos + 20) % 30 >= 25) {
                    food->eat_food(playerCellX + 1, playerCellY);
                    return true;
                }
            }
        } break;
        case 2: {
            int any_food = food->get_food_by_coords(playerCellX, playerCellY + 1);
            if (any_food) {
                if ((yPos + 20) % 30 >= 25) {
                    food->eat_food(playerCellX, playerCellY + 1);
                    return true;
                }
            }
        }
        case 3: {
            int any_food = food->get_food_by_coords(playerCellX - 1, playerCellY);
            if (any_food) {
                if ((xPos - 20) % 30 >= 25) {
                    food->eat_food(playerCellX - 1, playerCellY);
                    return true;
                }
            }
        }
        case 4: {
            int any_food = food->get_food_by_coords(playerCellX, playerCellY - 1);
            if (any_food) {
                if ((yPos - 20) % 30 >= 25) {
                    food->eat_food(playerCellX, playerCellY - 1);
                    return true;
                }
            }
        }
        default: break;
    }
    return false;
}

bool Player::GhostCollisions(Ghost *ghosts[4]) {

    for (int i = 0; i < 4; ++i) {
        if (ghosts[i]->GetX() + 40 >= xPos && ghosts[i]->GetX() <= xPos + 40 &&
            ghosts[i]->GetY() + 40 >= yPos && ghosts[i]->GetY() <= yPos + 40) return true;
    }
    return false;
}

void Player::RenderPlayer() {
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
    food->drawFood();
}