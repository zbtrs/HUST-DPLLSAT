//
// Created by zbtrs on 2022/8/20.
//

#ifndef HUST_DPLLSAT_HEADER_H
#define HUST_DPLLSAT_HEADER_H
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#define ROW 9
#define COL 9
using namespace std;

const string filePath = R"(D:\HUST-DPLLSAT\samples\)";


typedef struct Data {
    int data = 0;
    Data *nextData{};
}Data;

typedef struct Head{
    int num = 0;
    Data *nextData{};
    Head *nextHead{};
}Head;

struct Config{
    int holes = 0;
    string filename = "";
    int opt = 0;
};

struct Article{
    int positive = 0,negative = 0;
};

void terminalTips();
Head* initCnf(int &, string &);
bool DPLL(Head*,int*,int);
string initSudoku(int);
void printCompleteSudoku(int*, int);


#endif //HUST_DPLLSAT_HEADER_H
