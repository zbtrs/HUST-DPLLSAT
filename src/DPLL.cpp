//
// Created by zbtrs on 2022/8/20.
//

#include "header.h"

bool isEmptyClause(Head* LinkedList) {
    Head* PHead = LinkedList;
    while (PHead != nullptr) {
        if (PHead -> num == 0) {
            return true;
        }
        PHead = PHead -> nextHead;
    }
    return false;
}

Head* findSingleClause(Head* LinkedList) {
    while (LinkedList != nullptr) {
        if (LinkedList -> num == 1) {
            return LinkedList;
        }
        LinkedList = LinkedList -> nextHead;
    }
    return nullptr;
}

Head* addSingleClause(Head* LinkedList,int var) {
    Head* addHead = new Head;
    Data* addData = new Data;
    addData -> data = var;
    addData -> nextData = nullptr;
    addHead -> nextData = addData;
    addHead -> num = 1;
    addHead -> nextHead = LinkedList;
    LinkedList = addHead;
    return LinkedList;
}

void deleteHead(Head* Clause,Head *&LinkedList) {
    if (!Clause)
        return;
    if (Clause == LinkedList) {
        LinkedList = Clause -> nextHead;
    } else {
        for (Head* front = LinkedList; front != nullptr; front = front -> nextHead) {
            if (front -> nextHead == Clause) {
                front -> nextHead = Clause -> nextHead;
            }
        }
    }
}