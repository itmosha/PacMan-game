#pragma once
#include "Game.h"
#include "iostream"
#include "list"
#include "algorithm"
#include "TextObject.h"

struct res {
    char name[16];
    int pts;
};

class Result {
public:
    Result();
    ~Result() = default;

    void AddResult(const char playerName[16], int points);
    void PrintList();
    void ClearList();

    void SaveToFile();

    std::vector<res> records;
};