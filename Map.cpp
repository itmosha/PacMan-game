#include "Map.h"
#include "GameObject.h"
#include "TextureCreator.h"
#include "fstream"
GameObject* map_texture;

Map::Map() {
    loadMap();
    map_texture = new GameObject("../assets/Map.png");
}

bool Map::get_map_element(int row, int column) {
    return map[row][column];
}

void Map::loadMap() {
    std::ifstream in;
    in.open("other/MapStructure.txt");

    for (int row = 0; row < 33; row++) {
        for (int column = 0; column < 28; column++) {
            in >> map[row][column];
        }
    }
    in.close();
}

void Map::drawMap() {
    map_texture->Update(990, 840, 0, 0, 990, 840, 0, 0);
    map_texture->Render();
}