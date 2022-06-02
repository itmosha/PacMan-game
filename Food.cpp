#include "Food.h"
#include "GameObject.h"
#include "fstream"

Food::Food() {
    loadFood();
    for (int i = 0; i < FOOD_COUNT; ++i) {
        food_array[i] = new GameObject("../assets/Food.png", food_coords[i].x + 5, food_coords[i].y + 5);
    }
}

void Food::loadFood() {
    std::ifstream in;
    in.open("../other/FoodCoordinates.txt");

    int x, y, i = 0;
    while (in >> x >> y) {

        is_eaten[i] = false;

        coords crds;
        crds.x = x; crds.y = y;
        food_coords[i] = crds;
        i++;
    }
    in.close();
}

void Food::drawFood() {
    for (int i = 0; i < FOOD_COUNT; ++i) {
        if (!is_eaten[i]) {
            food_array[i]->Update(20, 20, 0, 0, food_coords[i].x*30 + 5, food_coords[i].y*30 + 5);
            food_array[i]->Render();
        }
    }
}