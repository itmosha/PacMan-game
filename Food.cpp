#include "Food.h"
#include "GameObject.h"
#include "fstream"

Food::Food() {

    int bonuses[3];
    for (int i = 0; i < 3; ++i) bonuses[i] = rand() % 244;

    for (int i = 0; i < FOOD_COUNT; ++i) is_bonus[i] = false;
    for (int i = 0; i < 3; ++i) is_bonus[bonuses[i]] = true;

    loadFood();

    for (int i = 0; i < FOOD_COUNT; ++i) {
        food_array[i] = new GameObject("../assets/Food.png");
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

            if (is_bonus[i]) {
                food_array[i]->Update(20, 20, 20, 0, 20, 20, food_coords[i].x * 30 + 5, food_coords[i].y * 30 + 5);
                food_array[i]->Render();
            }
            else {
                food_array[i]->Update(20, 20, 0, 0, 20, 20, food_coords[i].x * 30 + 5, food_coords[i].y * 30 + 5);
                food_array[i]->Render();
            }
        }
    }
}

// 0 if there is no food
// 1 if there is regular food
// 2 if there is a bonus

int Food::get_food_by_coords(int x, int y) {
    bool found = false;
    for (int i = 0; i < FOOD_COUNT; ++i) {
        if (food_coords[i].x == x && food_coords[i].y == y) {
            if (is_eaten[i]) return 0;
            else {
                if (is_bonus[i]) return 2;
                else return 1;
            }
        }
    }
    return 0;
}

void Food::eat_food(int x, int y) {
    for (int i = 0; i < FOOD_COUNT; ++i) {
        if (food_coords[i].x == x && food_coords[i].y == y) {
            is_eaten[i] = true;
            break;
        }
    }
}