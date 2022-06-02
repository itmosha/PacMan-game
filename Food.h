#pragma once
#include "GameObject.h"
#define FOOD_COUNT 244

struct coords {
    int x, y;
};

class Food {
private:
    GameObject* food_array[FOOD_COUNT];
    bool is_eaten[FOOD_COUNT];
    coords food_coords[FOOD_COUNT];

public:
    Food();

    void loadFood();
    void drawFood();

    ~Food() = default;
};