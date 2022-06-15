#pragma once

class CollisionChecker {
private:
    int collisionMap[33][28];
public:
    CollisionChecker();

    bool RightWallCollision(int x, int y);
    bool LeftWallCollision(int x, int y);
    bool DownWallCollision(int x, int y);
    bool UpWallCollision(int x, int y);
};