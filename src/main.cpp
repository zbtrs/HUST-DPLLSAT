//
// Created by zbtrs on 2022/8/20.
//

#include "header.h"

void terminalTips() {
    printf("                    Menu for SAT Solver based on DPLL                   \n");
    printf("------------------------------------------------------------------------\n");
    printf("                     1.Sudoku     2.SAT    0.Exit                       \n");
    printf("------------------------------------------------------------------------\n");
}

void printAnswer(clock_t startTime,clock_t endTime,bool flag,int *result,int varNum,string filename) {
    string outputFile = filePath + filename;
    ofstream fos(outputFile);
    if (!fos.is_open()) {
        cout << "error! Can't open a new file\n" << endl;
        exit(-1);
    }
    if (flag) {
        fos << "S " << 1 << endl;
        fos << "V ";
        for (int i = 0; i < varNum; i++) {
            if (result[i] == 1) {
                fos << i + 1 << " ";
            } else if (result[i] == 0) {
                fos << -(i + 1) << " ";
            } else {
                fos << i + 1 << " ";
            }
        }
        fos << endl;
    } else {
        fos << "S " << -1 << endl;
        fos << "V " << endl;
    }
    fos<< "T " << (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000.0 << " ms" << endl;
    fos.close();
}

void printCompleteSudoku(int *result, int varNum) {
    int a[9][9] = {0},b[9][9] = {0};
    for (int i = 0; i < varNum / 2; i++) {
        if (result[i] > 0) {
            int t = i;
            int x = t / 81;
            int y = (t - x * 81) / 9;
            a[x][y] = t - x * 81 - y * 9 + 1;
        }
    }
    for (int i = varNum / 2; i < varNum; i++) {
        if (result[i] > 0) {
            int t = i - 729;
            int x = t / 81;
            int y = (t - x * 81) / 9;
            b[x][y] = t - x * 81 - y * 9 + 1;
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 6; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << a[i][j] << " ";
        }
        for (int j = 3; j < 9; j++) {
            cout << b[i - 6][j] << " ";
        }
        cout << endl;
    }
    for (int i = 3; i < 9; i++) {
        for (int j = 1; j <= 12; j++) {
            cout << " ";
        }
        for (int j = 0; j < 9; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

}

int main() {
    terminalTips();
    int choice = 0;
    cin >> choice;
    while (choice) {
        if (choice == 1) {
            string filename = initSudoku();

            int varnum = 0;
            Head* LinkedList = initCnf(varnum,filename);
            int *result = new int[varnum];
            memset(result,0,sizeof(int) * varnum);
            clock_t startTime,endTime;
            startTime = clock();
            bool flag = DPLL(LinkedList,result);
            endTime = clock();
            printAnswer(startTime,endTime,flag,result,varnum,"sudoku.res");
            printCompleteSudoku(result,varnum);


            //TODO: Sudoku
        } else if (choice == 2) {
            //TODO 将文件操作放到配置文件或者环境变量中
            int varnum;
            string file = "problem1-20";
            cin >> file;
            string suffix = ".cnf";
            string filename = file + suffix;
            Head* LinkedList = initCnf(varnum,filename);
            int *result = new int[varnum];
            memset(result,0,sizeof(int) * varnum);
            clock_t startTime,endTime;
            string outputFile = file + ".res";
            startTime = clock();
            bool flag = DPLL(LinkedList,result);
            endTime = clock();
            printAnswer(startTime,endTime,flag,result,varnum,outputFile);

        } else if (choice == 0) {
            break;
        } else {
            cout << "Please input the right num! " << endl;
            exit(-1);
        }
        terminalTips();
        cin >> choice;
    }

    return 0;
}

