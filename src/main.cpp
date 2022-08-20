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
    int temp = 0;
    string file = "problem1-20.cnf";
    initCnf(temp,file);
    int choice = 0;
    cin >> choice;
    while (choice) {
        if (choice == 1) {
            //TODO: Sudoku
        } else if (choice == 2) {
            //TODO: SAT
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

