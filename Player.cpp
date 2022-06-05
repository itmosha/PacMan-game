#include "Player.h"
const int PLAYER_SPEED = 2;

Food* food;

Player::Player() {
    objectTexture = TextureCreator::loadTexture("../assets/Character.png");
    collisionChecker = new CollisionChecker();
    food = new Food();

    xPos = 400;
    yPos = 685;
    direction = 0;
}

void Player::SetDirection(int dir) { direction = dir; }

bool Player::UpdatePlayer() {

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
            if (!collisionChecker->RightWallCollision(xPos, yPos)) xPos += PLAYER_SPEED;
            break;
        case 2:
            if (!collisionChecker->DownWallCollision(xPos, yPos)) yPos += PLAYER_SPEED;
            break;
        case 3:
            if (!collisionChecker->LeftWallCollision(xPos, yPos)) xPos -= PLAYER_SPEED;
            break;
        case 4:
            if (!collisionChecker->UpWallCollision(xPos, yPos)) yPos -= PLAYER_SPEED;
            break;
        default:
            break;
    }

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

void Player::RenderPlayer() {
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
    food->drawFood();
}