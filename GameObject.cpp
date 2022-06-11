#include "GameObject.h"
#include "TextureCreator.h"

GameObject::GameObject(const char *texturesheet) {
    objectTexture = TextureCreator::loadTexture(texturesheet);

    xPos = 0;
    yPos = 0;
}

void GameObject::Update(int sourceH, int sourceW, int sourceX, int sourceY, int destH, int destW, int destX, int destY) {

    sourceRectangle.h = sourceH;
    sourceRectangle.w = sourceW;
    sourceRectangle.x = sourceX;
    sourceRectangle.y = sourceY;

    destinationRectangle.h = destH;
    destinationRectangle.w = destW;
    destinationRectangle.x = destX;
    destinationRectangle.y = destY;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}