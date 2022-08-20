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

int main() {
    terminalTips();
    int choice = 0;
    cin >> choice;
    while (choice) {
        if (choice == 1) {
            string filename = initSudoku();
            //TODO: Sudoku
        } else if (choice == 2) {
            //TODO 将文件操作放到配置文件或者环境变量中
            int varnum;
            string filePath = R"(D:\HUST-DPLLSAT\samples\)";
            string file = "problem1-20.cnf";
            Head* LinkedList = initCnf(varnum,file);
            int result[varnum];
            clock_t startTime,endTime;
            string outputFile = filePath + "solution.res";
            ofstream fos(outputFile);
            if (!fos.is_open()) {
                cout << "error! Can't open a new file\n" << endl;
                exit(-1);
            }
            startTime = clock();
            bool flag = DPLL(LinkedList,result);
            endTime = clock();

            if (flag) {
                fos << "S " << 1 << endl;
                fos << "V ";
                for (int i = 0; i < varnum; i++) {
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

        } else if (choice == 0) {
            break;
        } else {
            cout << "Please input the right num! " << endl;
            exit(-1);
        }
        cin >> choice;
    }

    return 0;
}

