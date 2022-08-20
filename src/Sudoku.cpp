//
// Created by zbtrs on 2022/8/20.
//

#include "header.h"

void randomFirstRow(int a[],int n) {
    srand((unsigned)time(nullptr));
    int vis[10];
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {  //如果已经填过了
            vis[a[i]] = 1;
        } else {
            a[i] = rand() % 9 + 1;
            while (vis[a[i]]) {
                a[i] = rand() % 9 + 1;
            }
            vis[a[i]] = 1;
        }
    }
}

bool fillLast(int a[][COL],int row,int col) {
    //当前要填第row行col列的格子
    if (row == ROW) {
        return true;
    }
    if (col == COL) {
        return fillLast(a,row + 1,0);
    }
    if (a[row][col] != 0) {
        //如果已经填过了
        return fillLast(a,row,col + 1);
    }
    int vis[10];
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < 9; i++) {
        vis[a[row][i]] = 1;
        vis[a[i][col]] = 1;
    }
    for (int i = row / 3 * 3; i < row / 3 * 3 + 3; i++) {
        for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++) {
            vis[a[i][j]] = 1;
        }
    }
    for (int i = 1; i <= 9; i++) {
        if (vis[i]) {
            continue;
        }
        a[row][col] = i;
        if (fillLast(a,row,col + 1)) {
            return true;
        }
    }
    a[row][col] = 0;
    return false;
}

void createSudoku(int a[][COL]) {
    randomFirstRow(a[0],COL);
    fillLast(a,1,0);
}

void print(const int a[][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void putHole(int a[][COL],int b[][COL],int holeNum) {
    srand((unsigned)time(nullptr));
    for (int i = 1; i <= holeNum; i++) {
        int whichSudoku = rand() % 2, x = rand() % 9, y = rand() % 9;
        if (whichSudoku == 0) {
            //挖第一个数独上的洞
            while (a[x][y] == 0) {  //已经被挖过了
                x = rand() % 9;
                y = rand() % 9;
            }
            a[x][y] = 0;
            if (x >= 6 && y >= 6) {
                b[x - 6][y - 6] = 0;
            }
        } else {
            while (b[x][y] == 0) {
                x = rand() % 9;
                y = rand() % 9;
            }
            b[x][y] = 0;
            if (x <= 2 && y <= 2) {
                a[x + 6][y + 6] = 0;
            }
        }
    }
}

string initSudoku() {
    int sudoku1[ROW][COL] = {0};
    int sudoku2[ROW][COL] = {0};
    int holeNum = 5;
    //先生成第一个数独，再来生成第二个
    createSudoku(sudoku1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sudoku2[i][j] = sudoku1[i + 6][j + 6];
        }
    }
    createSudoku(sudoku2);
    putHole(sudoku1,sudoku2,holeNum);
    print(sudoku1);
    print(sudoku2);

    //TODO
    return "";
}