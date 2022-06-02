#include "GameObject.h"
#include "TextureCreator.h"

GameObject::GameObject(const char *texturesheet, int x, int y) {
    objectTexture = TextureCreator::loadTexture(texturesheet);

    xPos = x;
    yPos = y;
}

void GameObject::Update(int H, int W, int sourceX, int sourceY, int destX, int destY) {

    sourceRectangle.h = H;
    sourceRectangle.w = W;
    sourceRectangle.x = sourceX;
    sourceRectangle.y = sourceY;

    destinationRectangle.h = H;
    destinationRectangle.w = W;
    destinationRectangle.x = destX;
    destinationRectangle.y = destY;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}

