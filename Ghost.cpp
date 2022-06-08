#include "Ghost.h"
#include "TextureCreator.h"
#include "vector"

Ghost::Ghost(int ghost_type) {
    objectTexture = TextureCreator::loadTexture("../assets/Ghosts.png");
    collisionCheckerGhost = new CollisionChecker;

    xPos = 0;
    yPos = 0;

    killed = false;
    is_active = false;
    type = ghost_type;
    direction = 0;
}

void Ghost::UpdateGhost(int points) {

    int sourceX;
    switch(type) {
        case 1: sourceX = 0; break;
        case 2: sourceX = 40; break;
        case 3: sourceX = 80; break;
        case 4: sourceX = 120; break;
    }


    switch (type) {
        case 1: {
            if (!is_active) {
                xPos = 400;
                yPos = 325;
                is_active = true;
            }
        } break;
        case 2: {
            if (points >= 75 && !is_active) {
                xPos = 400;
                yPos = 325;
                is_active = true;
            } else if (!is_active){
                destinationRectangle.x = xPos = 345;
                destinationRectangle.y = yPos = 415;
            }
        } break;
        case 3: {
            if (points >= 125 && !is_active) {
                xPos = 400;
                yPos = 325;
                is_active = true;
            } else if (!is_active) {
                destinationRectangle.x = xPos = 400;
                destinationRectangle.y = yPos = 415;
            }
        } break;
        case 4: {
            if (points >= 175 && !is_active) {
                xPos = 400;
                yPos = 325;
                is_active = true;
            } else if (!is_active) {
                destinationRectangle.x = xPos = 455;
                destinationRectangle.y = yPos = 415;
            }
        }
        default: break;
    }

    if (is_active && !direction) {
        std::vector<int> possibleDirections;
        if (!collisionCheckerGhost->RightWallCollision(xPos, yPos)) possibleDirections.push_back(1);
        if (!collisionCheckerGhost->DownWallCollision(xPos, yPos)) possibleDirections.push_back(2);
        if (!collisionCheckerGhost->LeftWallCollision(xPos, yPos)) possibleDirections.push_back(3);
        if (!collisionCheckerGhost->UpWallCollision(xPos, yPos)) possibleDirections.push_back(4);

        direction = possibleDirections[clock() % possibleDirections.size()];
    }
        switch (direction) {
            case 1: {
                if (!collisionCheckerGhost->RightWallCollision(xPos, yPos)) xPos+= GHOST_SPEED;
                else direction = 0;
            } break;
            case 2: {
                if (!collisionCheckerGhost->DownWallCollision(xPos, yPos)) yPos+= GHOST_SPEED;
                else direction = 0;
            } break;
            case 3: {
                if (!collisionCheckerGhost->LeftWallCollision(xPos, yPos)) xPos-= GHOST_SPEED;
                else direction = 0;
            } break;
            case 4: {
                if (!collisionCheckerGhost->UpWallCollision(xPos, yPos)) yPos-= GHOST_SPEED;
                else direction = 0;
            } break;
            default: break;
    }
    sourceRectangle.h = 40;
    sourceRectangle.w = 40;
    sourceRectangle.x = sourceX;
    sourceRectangle.y = 0;

    destinationRectangle.h = 40;
    destinationRectangle.w = 40;
    destinationRectangle.x = xPos;
    destinationRectangle.y = yPos;

    Update(40, 40, sourceX, 0, 40, 40, destinationRectangle.x, destinationRectangle.y);
}

bool Ghost::CheckActive() { return is_active; }
void Ghost::UnableGhost() { is_active = false; }
void Ghost::Kill(){ killed = true; };

void Ghost::RenderGhost() {
    if (!killed) {
        SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
    }
}