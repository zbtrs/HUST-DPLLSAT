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

void deleteData(int object,Head *&LinkedList) {
    for (Head* pHead = LinkedList; pHead != nullptr; pHead = pHead -> nextHead) {
        for (Data* rear = pHead -> nextData; rear != nullptr; rear = rear -> nextData) {
            if (rear -> data == object) {  //删除整行
                deleteHead(pHead,LinkedList);
            } else if (abs(rear -> data) == abs(object)) {
                //绝对值相同，只删除这个节点
                if (rear == pHead -> nextData) {
                    //如果是头部节点
                    pHead -> nextData = rear -> nextData;
                    pHead -> num--;
                } else {
                    for (Data* front = pHead -> nextData; front != nullptr; front = front -> nextData) {
                        if (front -> nextData == rear) {
                            front -> nextData = rear -> nextData;
                            pHead -> num--;
                        }
                    }
                }
            }
        }
    }
}

void printResult(int *result,int varNum) {
    cout << "V ";
    for (int i = 0; i < varNum; i++) {
        if (result[i] == 1) {
            cout << i + 1 << " ";
        } else if (result[i] == 0) {
            cout << -(i + 1) << " ";
        } else {  //第三种情况是变元，可true可false
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

Head* duplication(Head* LinkedList) {
    //复制，先创建第一行
    Head* lastHead = LinkedList;
    Head* newHead = new Head;
    newHead -> num = lastHead -> num;
    Head* pHead = newHead;
    //第一个Data
    Data* newData = new Data;
    Data* firstLastData = lastHead -> nextData;
    newData -> data = firstLastData -> data;
    pHead -> nextData = newData;
    //第一行
    for (firstLastData = firstLastData -> nextData; firstLastData != nullptr; firstLastData = firstLastData -> nextData) {
        Data* temp = new Data;
        temp -> data = firstLastData -> data;
        newData -> nextData = temp;
        newData = newData -> nextData;
    }
    //后面若干行
    for (lastHead = lastHead ->nextHead; lastHead != nullptr; lastHead = lastHead -> nextHead) {
        Head* tempHead = new Head;
        Data* tempData = new Data;
        tempHead -> num = lastHead -> num;
        pHead -> nextHead = tempHead;
        pHead = pHead -> nextHead;
        Data* lastData = lastHead -> nextData;
        tempData -> data = lastData -> data;
        pHead -> nextData = tempData;
        for (lastData = lastData -> nextData; lastData != nullptr; lastData = lastData -> nextData) {
            Data* temp = new Data;
            temp -> data = lastData -> data;
            tempData -> nextData = temp;
            tempData = tempData -> nextData;
        }
        tempData -> nextData = nullptr;
    }
    pHead -> nextHead = nullptr;

    return newHead;
}

bool DPLL(Head* LinkedList,int* result) {
    Head* pFind = LinkedList;
    Head* singleClause = findSingleClause(pFind);
    while (singleClause != nullptr) {
        int data = singleClause -> nextData -> data;
        if (data > 0) {
            result[abs(data) - 1] = 1;
        } else {
            result[abs(data) - 1] = 0;
        }
        deleteHead(singleClause,LinkedList);  //删除单子句
        deleteData(data,LinkedList);   //化简包含相反值的子句
        if (!LinkedList) {
            return true;
        } else if (isEmptyClause(LinkedList)) {
            return false;
        }
        pFind = LinkedList;
        singleClause = findSingleClause(pFind);
    }
    int data = LinkedList -> nextData -> data;
    Head* last = duplication(LinkedList);
    Head* newLinkedList = addSingleClause(LinkedList,data);
    //分裂策略
    if (DPLL(newLinkedList,result)) {
        return true;
    } else {
        Head* newLinkedList2 = addSingleClause(last,-data);
        return DPLL(newLinkedList2,result);
    }

}

