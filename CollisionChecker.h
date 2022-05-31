#pragma once

class CollisionChecker {
private:
    int collisionMap[33][28];
public:
    CollisionChecker();

    bool RightCollision(int x, int y);
    bool LeftCollision(int x, int y);
    bool DownCollision(int x, int y);
    bool UpCollision(int x, int y);
};