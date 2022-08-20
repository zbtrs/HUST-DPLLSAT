//
// Created by zbtrs on 2022/8/20.
//

#include "header.h"

ifstream openFile(string file) {
    ifstream fis(file);
    if (!fis) {
        cout << "Error! File can't open!" << endl;
        exit(-1);
    }
    return fis;
}

Head* initCnf(int &varNum, string &filename) {
    //打开文件
    //TODO:改变代码结构
    string filePath = R"(D:\HUST-DPLLSAT\samples\)";
    string file = filePath + filename;
    ifstream fis = openFile(file);
    char ch,readbuf[1010];
    fis >> ch;
    while (ch != 'p') {
        fis.getline(readbuf,1010);
        fis >> ch;
    }
    string cnf;
    int clauseNum;
    fis >> cnf >> varNum >> clauseNum;
    fis.get();

    //接下来根据每一行读入的子句来构建链表
    //TODO 小心内存泄漏
    Head* HEAD = new Head;
    Head* headRear = HEAD;
    Head* END = new Head;
    for (int i = 0; i < clauseNum; i++) {
        int temp;
        fis >> temp;
        Data* front = new Data;
        front -> data = temp;
        headRear -> nextData = front;
        headRear -> num++;
        fis >> temp;
        while (temp != 0) {
            Data* rear = new Data;
            front -> nextData = rear;
            rear -> data = temp;
            front = front -> nextData;
            headRear -> num++;
            fis >> temp;
        }
        front -> nextData = nullptr;
        fis.get();  //换行
        Head* tp = new Head;
        headRear -> nextHead = tp;
        END = headRear;
        headRear = headRear -> nextHead;
    }
    END -> nextHead = nullptr;

    //输出整个链表
    Head* Phead = HEAD;
    Data* front = nullptr;
    cout << "CnfParser" << endl;
    while (Phead != nullptr) {
        front = Phead -> nextData;
        while (front != nullptr) {
            cout << front -> data << " ";
            front = front -> nextData;
        }
        cout << endl;
        Phead = Phead -> nextHead;
    }

    return HEAD;
}