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

string getCnf(int a[][COL],int b[][COL]) {
    ofstream fos(filePath + "sudoku.cnf");
    if (!fos.is_open()) {
        cout << "Error! Can't open file" << endl;
        exit(-1);
    }
    int tot = 0,cnt = 0;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (a[i][j] != 0) {
                tot++;
            }
            if (b[i][j] != 0) {
                tot++;
            }
        }
    }
    fos << "p cnf 1458 " << 29970 + tot << " " << endl;
    //对于已经填了的，直接生成单语句
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (a[i][j] != 0) {
                fos << i * 81 + j * 9 + a[i][j] << " " << 0 << endl;
            }
            if (b[i][j] != 0) {
                fos << 729 + i * 81 + j * 9 + b[i][j] << " " << 0 << endl;
            }
        }
    }
    //单个格子
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            for (int k = 1; k <= 9; k++) {
                fos << (i - 1) * 81 + (j - 1) * 9 + k << " ";
            }
            fos << 0 << endl;
            cnt++;
            for (int k = 1; k <= 9; k++) {
                fos << 729 + (i - 1) * 81 + (j - 1) * 9 + k << " ";
            }
            fos << 0 << endl;
            cnt++;
            for (int k = 1; k <= 9; k++) {
                for (int p = k + 1; p <= 9; p++) {
                    fos << -((i - 1) * 81 + (j - 1) * 9 + k) << " " << -((i - 1) * 81 + (j - 1) * 9 + p) << " " << 0 << endl;
                    fos << -(729 + (i - 1) * 81 + (j - 1) * 9 + k) << " " << -(729 + (i - 1) * 81 + (j - 1) * 9 + p) << " " << 0 << endl;
                    cnt += 2;
                }
            }
            //cnt += 2;
        }
    }
    //行
    for (int i = 1; i <= 9; i++) {
        for (int k = 1; k <= 9; k++) {
            for (int j = 1; j <= 9; j++) {
                fos << ((i - 1) * 81 + (j - 1) * 9 + k) << " ";
            }
            fos << 0 << endl;
            for (int j = 1; j <= 9; j++) {
                fos << (729 + (i - 1) * 81 + (j - 1) * 9 + k) << " ";
            }
            fos << 0 << endl;
            cnt += 2;
            for (int p = 1; p <= 9; p++) {
                for (int q = p + 1; q <= 9; q++) {
                    fos << -((i - 1) * 81 + (p - 1) * 9 + k) << " " << -((i - 1) * 81 + (q - 1) * 9 + k) << " " << 0 << endl;
                    fos << -(729 + (i - 1) * 81 + (p - 1) * 9 + k) << " " << -(729 + (i - 1) * 81 + (q - 1) * 9 + k) << " " << 0 << endl;
                    cnt += 2;
                }
            }
        }
    }
    //列
    for (int j = 1; j <= 9; j++) {
        for (int k = 1; k <= 9; k++) {
            for (int i = 1; i <= 9; i++) {
                fos << ((i - 1) * 81 + (j - 1) * 9 + k) << " ";
            }
            fos << 0 << endl;
            for (int i = 1; i <= 9; i++) {
                fos << (729 + (i - 1) * 81 + (j - 1) * 9 + k) << " ";
            }
            fos << 0 << endl;
            cnt += 2;
            for (int p = 1; p <= 9; p++) {
                for (int q = p + 1; q <= 9; q++) {
                    fos << -((p - 1) * 81 + (j - 1) * 9 + k) << " " << -((q - 1) * 81 + (j - 1) * 9 + k) << " " << 0 << endl;
                    fos << -(729 + (p - 1) * 81 + (j - 1) * 9 + k) << " " << -(729 + (q - 1) * 81 + (j - 1) * 9 + k) << " " << 0 << endl;
                    cnt += 2;
                }
            }
        }
    }
    //3*3
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int x1 = x * 3 + 1,x2 = x * 3 + 3;
            int y1 = y * 3 + 1,y2 = y * 3 + 3;
            for (int k = 1; k <= 9; k++) {
                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        fos << (i - 1) * 81 + (j - 1) * 9 + k << " ";
                    }
                }
                fos << 0 << endl;
                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        fos << 729 + (i - 1) * 81 + (j - 1) * 9 + k << " ";
                    }
                }
                fos << 0 << endl;
                cnt += 2;

                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        for (int p = x1; p <= x2; p++) {
                            for (int q = y1; q <= y2; q++) {
                                if (i == p && j == q) {
                                    continue;
                                }
                                fos << -((i - 1) * 81 + (j - 1) * 9 + k) << " " << -((p - 1) * 81 + (q - 1) * 9 + k) << " " << 0 << endl;
                                fos << -(729 + (i - 1) * 81 + (j - 1) * 9 + k) << " " << -(729 + (p - 1) * 81 + (q - 1) * 9 + k) << " " << 0 << endl;
                                cnt += 2;
                            }
                        }
                    }
                }
            }
        }
    }
    //公共部分
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 1; k <= 9; k++) {
                fos << 0 - ((i + 6) * 81 + (j + 6) * 9 + k) << " " << (729 + i * 81 + j * 9 + k) << " " << 0 << endl;
                fos << ((i + 6) * 81 + (j + 6) * 9 + k) << " " << 0 - (729 + i * 81 + j * 9 + k) << " " << 0 << endl;
                cnt += 2;
            }
        }
    }
    /*
    //行
    for (int y = 1; y <= 9; y++) {
        for (int z = 1; z <= 9; z++) {
            for (int x = 1; x <= 8; x++) {
                for (int i = x + 1; i <= 9; i++) {
                    fos << 0 - (x * 100 + y * 10 + z) << " " << 0 - (i * 100 + y * 10 + z) << " " << 0 << endl;
                    fos << 0 - (1000 + x * 100 + y * 10 + z) << " " << 0 - (1000 + i * 100 + y * 10 + z) << " " << 0 << endl;
                   // cnt += 2;
                }
            }
        }
    }
    //列
    for (int x = 1; x <= 9; x++) {
        for (int z = 1; z <= 9; z++) {
            for (int y = 1; y <= 8; y++) {
                for (int i = y + 1; i <= 9; i++) {
                    fos << 0 - (x * 100 + y * 10 + z) << " " << 0 - (x * 100 + i * 10 + z) << " " << 0 << endl;
                    fos << 0 - (1000 + x * 100 + y * 10 + z) << " " << 0 - (1000 + x * 100 + i * 10 + z) << " " << 0 << endl;
                   // cnt += 2;
                }
            }
        }
    }
    //3*3
    for (int z = 1; z <= 9; z++) {
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                for (int x = 1; x <= 3; x++) {
                    for (int y = 1; y <= 3; y++) {
                        for (int k = y + 1; k <= 3; k++) {
                            fos << 0 - (( 3 * i + x ) * 100 + (3 * j + y) * 10 + z)<<" "
                              << 0 - ((3 * i + x) * 100 + (3 * j + k) * 10 + z)<<" "<< 0 <<endl;
                            fos << 0 - (1000 + ( 3 * i + x ) * 100 + (3 * j + y) * 10 + z) << " "
                                << 0 - (1000 + (3 * i + x) * 100 + (3 * j + k) * 10 + z) << " " << 0 <<endl;
                           // cnt += 2;
                        }
                    }
                }
            }
        }
    }
    for (int z = 1; z <= 9; z++) {
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                for (int x = 1; x <= 3; x++) {
                    for (int y = 1; y <= 3; y++) {
                        for (int k = x + 1; k <= 3; k++) {
                            for (int l = 1; l <= 3; l++) {
                                fos << 0 - ((3*i+x)*100 + (3*j+y)*10 + z) << ' '
                                    << 0 - ((3*i+k)*100 + (3*j+l)*10 + z) << ' ' << 0 <<endl;
                                fos << 0 - (1000 + (3*i+x)*100 + (3*j+y)*10 + z) << ' '
                                    << 0 - (1000 + (3*i+k)*100 + (3*j+l)*10 + z) << ' ' << 0 <<endl;
                               // cnt += 2;
                            }
                        }
                    }
                }
            }
        }
    }
     */
    //cout << cnt << endl;
    fos.close();
    return "sudoku.cnf";
}

void printSudoku(int a[][COL],int b[][COL]) {
    ofstream fos(filePath + "sudoku.out");
    if (!fos.is_open()) {
        cout << "Error! Can't open file" << endl;
        exit(-1);
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            fos << to_string(a[i][j]) << " ";
        }
    }
    for (int i = 6; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fos << to_string(a[i][j]) << " ";
        }
        for (int j = 3; j < 9; j++) {
            fos << to_string(b[i - 6][j]) << " ";
        }
    }
    for (int i = 3; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fos << to_string(b[i][j]) << " ";
        }
    }
}

string initSudoku(int holes) {
    int sudoku1[ROW][COL] = {0};
    int sudoku2[ROW][COL] = {0};
    int holeNum = holes;
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
    printSudoku(sudoku1,sudoku2);

    return getCnf(sudoku1,sudoku2);
}

