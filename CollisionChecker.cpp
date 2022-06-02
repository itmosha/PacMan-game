#include "CollisionChecker.h"
#include "Game.h"
#include "Map.h"
#include "fstream"

CollisionChecker::CollisionChecker() {
    std::ifstream in;
    in.open("MapStructure.txt");

    for (int rows = 0; rows < 33; rows++) {
        for (int columns = 0; columns < 28; columns++) in >> collisionMap[rows][columns];
    }
    in.close();
}

bool CollisionChecker::RightCollision(int x, int y) {

    int luX = x + 5, luY = y + 10;
    int cellX = luX/30, cellY = luY/30;

    int upPoint = collisionMap[cellY][cellX + 1];

    luY = y + 30;
    cellY = luY/30;

    int downPoint = collisionMap[cellY][cellX];

    return upPoint || downPoint;
}

bool CollisionChecker::DownCollision(int x, int y) {

    int lrX = x + 10, lrY = y + 5;
    int cellX = lrX / 30, cellY = lrY / 30;

    int leftPoint = collisionMap[cellY + 1][cellX];

    lrX = x + 30;
    cellX = lrX / 30;
    int rightPoint = collisionMap[cellY + 1][cellX];

    return leftPoint || rightPoint;
}

bool CollisionChecker::LeftCollision(int x, int y) {

    int luX = x + 4, luY = y + 10;
    int cellX = luX / 30, cellY = luY / 30;

    int upPoint = collisionMap[cellY][cellX];

    luY = y + 30;
    cellY = luY / 30;

    int downPoint = collisionMap[cellY][cellX];

    return upPoint || downPoint;
}

bool CollisionChecker::UpCollision(int x, int y) {

    int lrX = x + 10, lrY = y + 4;
    int cellX = lrX / 30, cellY = lrY / 30;

    int leftPoint = collisionMap[cellY][cellX];

    lrX = x + 30;
    cellX = lrX / 30;

    int rightPoint = collisionMap[cellY][cellX];

    return leftPoint || rightPoint;
}