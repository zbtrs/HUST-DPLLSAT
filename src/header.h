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

using namespace std;

typedef struct Data {
    int data = 0;
    Data *nextData{};
}Data;

typedef struct Head{
    int num = 0;
    Data *nextData{};
    Head *nextHead{};
}Head;

void terminalTips();
Head* initCnf(int &, string &);
bool DPLL(Head*,int*);


#endif //HUST_DPLLSAT_HEADER_H
