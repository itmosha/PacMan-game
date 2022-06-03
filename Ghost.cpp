#include "Ghost.h"
#include "TextureCreator.h"

Ghost::Ghost(int ghost_type) {
    objectTexture = TextureCreator::loadTexture("../assets/Ghosts.png");
    xPos = 0;
    yPos = 0;
    is_active = false;
    type = ghost_type;
}

void Ghost::UpdateGhost(int points) {
    int sourceX;
    switch(type) {
        case 1: sourceX = 0; break;
        case 2: sourceX = 40; break;
        case 3: sourceX = 80; break;
        case 4: sourceX = 120; break;
    }

    int destX = 400, destY = 325;

    sourceRectangle.h = 40;
    sourceRectangle.w = 40;
    sourceRectangle.x = sourceX;
    sourceRectangle.y = 0;

    destinationRectangle.h = 40;
    destinationRectangle.w = 40;
    destinationRectangle.x = destX;
    destinationRectangle.y = destY;

    Update(40, 40, sourceX, 0, destinationRectangle.x, destinationRectangle.y);

    switch (type) {
        case 1: is_active = true; break;
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
}

void Ghost::RenderGhost() {
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}