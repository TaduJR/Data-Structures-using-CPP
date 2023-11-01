//
// Created by Natu on 4/30/2022.
//

#include "DoubleLinkedList.h"

template <class T>
DLinkedList<T>::DLinkedList() {
    head = nullptr;
    tail = nullptr;
    sorted = false;
};

template <class T>
DLinkedList<T>::DLinkedList(bool sorted) {
    head = nullptr;
    tail = nullptr;
    this->sorted = sorted;
}

template<class T>
DLinkedList<T>::DLinkedList(const DLinkedList &newDLinkedList) {
    //Unfinished
//    clear();
//    this = newDLinkedList;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
    clear();
}

template<class T>
bool DLinkedList<T>::isEmpty() {
    return head == nullptr;
}


template<class T>
void DLinkedList<T>::insertFirst(T data) {
    DNode<T> *p = new DNode<T>;
    if(p == nullptr) return;
    p->data = data;
    if(data > head->data) setSorted(false);
    insertNode(p, nullptr);
}

template<class T>
void DLinkedList<T>::insertBack(T data) {
    DNode<T> *p = new DNode<T>;
    if(p == nullptr) return;
    p->data = data;
    if(data < tail->data) setSorted(false);
    insertNode(p, tail);
}

template<class T>
bool DLinkedList<T>::insertBefore(T before, T data) {
    if(find(before) == nullptr) return false;
    DNode<T> *prev = find(before)->prev, *p = new DNode<T>;
    if(p == nullptr) return false;
    p->data = data;
    insertNode(p, prev);
    return true;
}

template<class T>
bool DLinkedList<T>::insertAfter(T after, T data) {
    if(find(after) == nullptr) return false;
    DNode<T> *prev = find(after);
    if(prev == nullptr) return false;
    DNode<T> *p = new DNode<T>;
    if(p == nullptr) return false;
    p->data = data;
    insertNode(p, prev);
    return true;
}

template<class T>
void DLinkedList<T>::insertRangeBeforeNode(DNode<T> *before, DLinkedList<T> range) {
    if(findNode(before) == nullptr) return;
    DNode<T> *prev = findNode(before)->prev, *newRangeHead = range.head, *p;
    if(prev == nullptr) prev = head;
    while(newRangeHead != nullptr) {
        p = new DNode<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
void DLinkedList<T>::insertRangeAfterNode(DNode<T> *after, DLinkedList<T> range) {
    if(findNode(after) == nullptr) return;
    DNode<T> *prev = findNode(after), *newRangeHead = range.head, *p;
    if(prev == nullptr) prev = tail;
    while(newRangeHead != nullptr) {
        p = new DNode<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
void DLinkedList<T>::insertRangeBefore(T before, DLinkedList<T> range) {
    if(find(before) == nullptr) return;
    DNode<T> *prev = find(before)->prev, *newRangeHead = range.head, *p;
    while(newRangeHead != nullptr) {
        p = new DNode<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
void DLinkedList<T>::insertRangeAfter(T after, DLinkedList<T> range) {
    if(find(after) == nullptr) return;
    DNode<T> *prev = find(after), *newRangeHead = range.head, *p;
    while(newRangeHead != nullptr) {
        p = new DNode<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
bool DLinkedList<T>::insert(T newData) {
    DNode<T> *prev = tail, *p = new DNode<T>;
    if(p == nullptr) return false;
    p->data = newData;
    if(sorted) prev = insertionSlot(p);
    insertNode(p, prev);
    return true;
}

template<class T>
bool DLinkedList<T>::removeFirst() {
    DNode<T> *p;
    p = deleteNode(nullptr);
    if(p == nullptr) return false;
    delete p;
    return true;
}

template<class T>
bool DLinkedList<T>::removeLast() {
    DNode<T> *p;
    p = deleteNode(tail->prev);
    if(p == nullptr) return false;
    delete p;
    return true;
}


template<class T>
bool DLinkedList<T>::removeRange(T rangeFirst, T rangeLast) {
    int rangeFirstIndex = determineIndex(rangeFirst), rangeLastIndex = determineIndex(rangeLast);
    if(rangeFirstIndex > rangeLastIndex) return false;
    DNode<T> *rangeFirstNode = find(rangeFirst), *rangeSecondNode = find(rangeLast);
    if(rangeFirstNode == nullptr || rangeSecondNode == nullptr) return false;
    DNode<T> *rangeFirstPrev = rangeFirstNode->prev, *finalNode = rangeSecondNode->next ,*p;
    while (true) {
        p = deleteNode(rangeFirstPrev);
        delete p;
        if(rangeFirstPrev->next == finalNode) break;
    }
    return true;
}

template<class T>
bool DLinkedList<T>::removeRangeNode(DNode<T> *rangeFirst, DNode<T> *rangeLast) {
    int rangeFirstIndex = determineIndexNode(rangeFirst), rangeLastIndex = determineIndexNode(rangeLast);
    if(rangeFirstIndex > rangeLastIndex) return false;
    DNode<T> *rangeFirstNode = findNode(rangeFirst), *rangeSecondNode = findNode(rangeLast);
    if(rangeFirstNode == nullptr || rangeSecondNode == nullptr) return false;
    DNode<T> *rangeFirstPrev = rangeFirstNode->prev, *finalNode = rangeSecondNode->next ,*p;
    while (true) {
        p = deleteNode(rangeFirstPrev);
        delete p;
        if(rangeFirstPrev->next == finalNode) break;
    }
    return true;
}

template<class T>
bool DLinkedList<T>::remove(T targetData) {
    DNode<T> *prev, *p;
    if(!nodeToDelete(targetData, prev)) return false;
    p = deleteNode(prev);
    delete p;
    return true;
}

template<class T>
bool DLinkedList<T>::update(T oldValue, T newValue) {
    DNode<T> *p = find(oldValue);
    if(p == nullptr) return false;
    p->data = newValue;
}

template<class T>
DNode<T> *DLinkedList<T>::find(T target) {
    DNode<T> *newHead = head;
    while(newHead != nullptr) {
        if(newHead->data == target) break;
        newHead = newHead->next;
    }
    return newHead;
}

template<class T>
DNode<T> *DLinkedList<T>::findNode(DNode<T> *target) {
    DNode<T> *newHead = head;
    while (newHead != nullptr) {
        if(target == newHead) break;
        newHead = newHead->next;
    }
    return newHead;
}


template<class T>
int DLinkedList<T>::determineIndex(T index) {
    int pos = 0;
    DNode<T>* newHead = head;
    bool found = false;
    while(newHead != nullptr) {
        if(index == newHead->data) {
            found = true;
            break;
        };
        newHead = newHead->next;
        ++pos;
    }
    if(!found) return -1;
    return pos;
}

template<class T>
int DLinkedList<T>::determineIndexNode(DNode<T> *indexNode) {
    int pos = 0;
    DNode<T>* newHead = head;
    bool found = false;
    while(newHead != nullptr) {
        if(indexNode == newHead->data) {
            found = true;
            break;
        };
        newHead = newHead->next;
        ++pos;
    }
    if(!found) return -1;
    return pos;
}

template<class T>
int DLinkedList<T>::count() {
    int counter = 0;
    DNode<T>* newHead = head;
    while(newHead != nullptr) {
        newHead = newHead->next;
        ++counter;
    }
    return counter;
}

template<class T>
void DLinkedList<T>::clear() {
    DNode<T> *prev;
    while(head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }
    head = tail = nullptr;
    sorted = false;
}


template<class T>
void DLinkedList<T>::setSorted(bool sorted) {
    if(this->sorted == true) this->sorted = sorted;
}

template<class T>
DLinkedList<T> DLinkedList<T>::copy() {
    DLinkedList<T> newLinkedList(sorted);
    DNode<T> *newHead = head;
    while(newHead != nullptr) {
        newLinkedList.insert(newHead->data);
        newHead = newHead->next;
    }
    return newLinkedList;
}

template<class T>
void DLinkedList<T>::operator=(const DLinkedList &linkedList) {
    //Unfinished
//    clear();
//    *this = linkedList.copy();
}

template<class T>
T &DLinkedList<T>::operator[](int idx) {
    int counter = 0;
    DNode<T> *newHead = head;
    while(newHead != nullptr) {
        if(idx == counter) return newHead->data;
        newHead = newHead->next;
        counter++;
    }
    return -1;
}

/* Private Members */
template<class T>
void DLinkedList<T>::insertNode(DNode<T> *p, DNode<T> *prev) {
    if(head == nullptr) {
        head = tail = p;
        p->prev = nullptr;
        p->next = nullptr;
    } else if (prev == nullptr) {
        head->prev = p;
        p->next = head;
        p->prev = nullptr;
        head = p;
    } else {
        DNode<T> *afterP = prev->next;
        if(afterP != nullptr) afterP->prev = p;
        p->next = prev->next;
        p->prev = prev;
        prev->next = p;
        if(prev == tail) tail = p;
    }
}

template<class T>
DNode<T>* DLinkedList<T>::deleteNode(DNode<T> *prev) {
    DNode<T> *p, *afterPos;
    if(head == tail) {
        p = head;
        head = nullptr;
    } else if(prev == nullptr) {
        p = head;
        head = head->next;
        head->prev = nullptr;
    } else {
        afterPos = prev->next;
        p = prev->next;
        prev->next = p->next;
        afterPos->prev = prev;
        if(tail == p) tail = prev;
    }
    return p;
}

template<class T>
DNode<T>* DLinkedList<T>::insertionSlot(DNode<T> *p) {
    DNode<T> *newHead = head, *prev = nullptr;
    while(newHead != nullptr) {
        if(newHead->data > p->data) break;
        prev = newHead;
        newHead = newHead->next;
    }
    return prev;
}

template<class T>
bool DLinkedList<T>::nodeToDelete(T targetData, DNode<T>* &prev) {
    DNode<T> *newHead = head;
    prev = nullptr;
    while(newHead != nullptr) {
        prev = newHead;
        if(targetData == newHead->data) return true;
        newHead = newHead->next;
    }
    return false;
}

template<class T>
void DLinkedList<T>::displayForward(void (*displayer)(T)) {
    DNode<T>* newFront = head;
    while (newFront != NULL) {
        displayer(newFront->data);
        newFront = newFront->next;
    }
}

template<class T>
void DLinkedList<T>::displayBackward(void (*displayer)(T)) {
    DNode<T>* newBack = head;
    while (newBack != NULL) {
        displayer(newBack->data);
        newBack = newBack->prev;
    }
}