#include "GameObject.h"
#include "TextureCreator.h"

GameObject::GameObject(const char *texturesheet, int x, int y) {
    objectTexture = TextureCreator::loadTexture(texturesheet);

    xPos = x;
    yPos = y;
}

void GameObject::Update(int sourceH, int sourceW, int sourceX, int sourseY) {

    sourceRectangle.h = sourceH;
    sourceRectangle.w = sourceW;
    sourceRectangle.x = sourceX;
    sourceRectangle.y = sourseY;

    destinationRectangle.h = sourceRectangle.h;
    destinationRectangle.w = sourceRectangle.w;
    destinationRectangle.x = xPos;
    destinationRectangle.y = yPos;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}