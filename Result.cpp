#include "Result.h"
#include "fstream"

bool comp(res a, res b) {
    return a.pts > b.pts;
}

Result::Result() {
    res item;
    FILE* f = fopen("results.bin", "rb");

    if (f) {
        while (fread(&item, sizeof(item), 1, f)) records.push_back(item);
        fclose(f);

        sort(records.begin(), records.end(), comp);
        if (records.size() > 10) records.resize(10);
    }
    else std::cout << "File opening error" << '\n';
}

void Result::AddResult(const char playerName[16], int points) {
    res item;
    item.pts = points;
    for (int i = 0; i < 16; ++i) item.name[i] = playerName[i];

    records.push_back(item);
    sort(records.begin(), records.end(), comp);
    if (records.size() > 10) records.resize(10);
}

void Result::PrintList() {
    FILE* f = fopen("temp.txt", "w");

    if (f) {
        remove("printfile.txt");
        fputs("Место | Очки | Имя\n", f);
        for (int i = 0; i < records.size(); ++i) {
            fputs(TextObject::score_toString(i+1), f);
            fputs("   |  ", f);
            std::cout << "1" << '\n';
            fputs(TextObject::score_toString(records[i].pts), f);
            fputs(" |  ", f);
            std::cout << "2" << '\n';
            fputs(records[i].name, f);
            fclose(f);
            std::cout << "3" << '\n';
        }
        rename("temp.txt", "printfile.txt");
    }
    else std::cout << "File opening error" << '\n';
}

void Result::ClearList() {

    FILE* f = fopen("temp.bin", "wb");
    remove("results.bin");
    rename("temp.dat", "results.bin");
    records.clear();
}

void Result::SaveToFile() {
    FILE *f = fopen("results.bin", "wb");

    if (f) {
        for (int i = 0; i < records.size(); ++i) fwrite(&(records[i]), sizeof(records[i]), 1, f);
        fclose(f);
    }
    else std::cout << "~File opening error" << '\n';
}


