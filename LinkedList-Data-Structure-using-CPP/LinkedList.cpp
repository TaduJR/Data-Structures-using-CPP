//
// Created by Natu on 4/29/2022.
//

#include <iostream>
#include "LinkedList.h"

template <class T>
void displayer(T data) {
    std::cout << data << ", ";
}

template <class T>
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    sorted = false;
}

template <class T>
LinkedList<T>::LinkedList(bool sorted) {
    head = tail = nullptr;
    this->sorted = sorted;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &linkedList) {
    //Unfinished
}

template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <class T>
bool LinkedList<T>::isEmpty() {
    return head == nullptr;
}


template<class T>
void LinkedList<T>::insertFirst(T data) {
    Node<T> *p = new Node<T>;
    if(p == nullptr) return;
    p->data = data;
    if(data > head->data) setSorted(false);
    insertNode(p, nullptr);
}

template<class T>
void LinkedList<T>::insertBack(T data) {
    Node<T> *p = new Node<T>;
    if(p == nullptr) return;
    p->data = data;
    if(data < tail->data) setSorted(false);
    insertNode(p, tail);
}

template<class T>
bool LinkedList<T>::insertBefore(T before, T data) {
    if(find(before) == nullptr) return false;
    Node<T> *prev = determinePrev(before), *p = new Node<T>;
    if(p == nullptr) return false;
    p->data = data;
    insertNode(p, prev);
    return true;
}

template<class T>
bool LinkedList<T>::insertAfter(T after, T data) {
    Node<T> *prev = find(after);
    if(prev == nullptr) return false;
    Node<T> *p = new Node<T>;
    if(p == nullptr) return false;
    p->data = data;
    insertNode(p, prev);
    return true;
}

template<class T>
void LinkedList<T>::insertRangeBefore(T before, LinkedList<T> range) {
    if(find(before) == nullptr) return;
    Node<T> *prev = determinePrev(before), *newRangeHead = range.head, *p;
    while(newRangeHead != nullptr) {
        p = new Node<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
void LinkedList<T>::insertRangeAfter(T after, LinkedList<T> range) {
    if(find(after) == nullptr) return;
    Node<T> *prev = find(after), *newRangeHead = range.head, *p;
    while(newRangeHead != nullptr) {
        p = new Node<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
void LinkedList<T>::insertRangeBeforeNode(Node<T> *before, LinkedList<T> range) {
    if(findNode(before) == nullptr) return;
    Node<T> *prev = determinePrevNode(before), *newRangeHead = range.head, *p;
    while(newRangeHead != nullptr) {
        p = new Node<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template<class T>
void LinkedList<T>::insertRangeAfterNode(Node<T> *after, LinkedList<T> range) {
    if(findNode(after) == nullptr) return;
    Node<T> *prev = findNode(after), *newRangeHead = range.head, *p;
    while(newRangeHead != nullptr) {
        p = new Node<T>;
        if(p == nullptr) return;
        p->data = newRangeHead->data;
        insertNode(p, prev);
        newRangeHead = newRangeHead->next;
        prev = p;
    }
    setSorted(false);
}

template <class T>
bool LinkedList<T>::insert(T newData) {
    Node<T> *prev = tail, *p = new Node<T>;
    p->data = newData;
    if(sorted) prev = insertionSlot(p);
    insertNode(p, prev);
    return true;
}


template<class T>
bool LinkedList<T>::removeFirst() {
    Node<T> *p;
    p = deleteNode(nullptr);
    if(p == nullptr) return false;
    delete p;
    return true;
}

template<class T>
bool LinkedList<T>::removeLast() {
    Node<T> *p;
    p = deleteNode(determineTailPrev());
    if(p == nullptr) return false;
    delete p;
    return true;
}


template<class T>
bool LinkedList<T>::removeRange(T rangeFirst, T rangeLast) {
    int rangeFirstIndex = determineIndex(rangeFirst), rangeLastIndex = determineIndex(rangeLast);
    if(rangeFirstIndex > rangeLastIndex) return false;
    Node<T> *rangeFirstNode = find(rangeFirst), *rangeSecondNode = find(rangeLast);
    if(rangeFirstNode == nullptr || rangeSecondNode == nullptr) return false;
    Node<T> *rangeFirstPrev = determinePrevNode(rangeFirstNode), *finalNode = rangeSecondNode->next ,*p;
    while (true) {
        p = deleteNode(rangeFirstPrev);
        delete p;
        if(rangeFirstPrev->next == finalNode) break;
    }
    return true;
}

template<class T>
bool LinkedList<T>::removeRangeNode(Node<T> *rangeFirst, Node<T> *rangeLast) {
    int rangeFirstIndex = determineIndexNode(rangeFirst), rangeLastIndex = determineIndexNode(rangeLast);
    if(rangeFirstIndex > rangeLastIndex) return false;
    Node<T> *rangeFirstNode = findNode(rangeFirst), *rangeSecondNode = findNode(rangeLast);
    if(rangeFirstNode == nullptr || rangeSecondNode == nullptr) return false;
    Node<T> *rangeFirstPrev = determinePrevNode(rangeFirstNode), *finalNode = rangeSecondNode->next ,*p;
    while (true) {
        p = deleteNode(rangeFirstPrev);
        delete p;
        if(rangeFirstPrev->next == finalNode) break;
    }
    return true;
}

template <class T>
bool LinkedList<T>::remove(T targetData) {
    Node<T> *prev, *p;
    if(!nodeToDelete(targetData, prev)) return false;
    p = deleteNode(prev);
    delete p;
    return true;
}

template <class T>
Node<T>* LinkedList<T>::find(T target) {
    Node<T> *newHead = head;
    while(newHead != nullptr) {
        if(newHead->data == target) break;
        newHead = newHead->next;
    }
    return newHead;
}


template<class T>
Node<T>* LinkedList<T>::determinePrevNode(Node<T> *target) {
    Node<T> *prev = nullptr, *newHead = head;
    while (newHead != nullptr) {
        if(target == newHead) break;
        prev = newHead;
        newHead = newHead->next;
    }
    return prev;
}

template<class T>
Node<T> *LinkedList<T>::determinePrev(T target) {
    Node<T> *prev = nullptr, *newHead = head;
    while (newHead != nullptr) {
        if(target == newHead->data) break;
        prev = newHead;
        newHead = newHead->next;
    }
    return prev;
}

template<class T>
Node<T> *LinkedList<T>::findNode(Node<T> *target) {
    Node<T> *newHead = head;
    while (newHead != nullptr) {
        if(target == newHead) break;
        newHead = newHead->next;
    }
    return newHead;
}

template<class T>
Node<T> *LinkedList<T>::determineTailPrev() {
    Node<T> *prev = nullptr, *newHead = head;
    while (newHead != nullptr) {
        prev = newHead;
        newHead = newHead->next;
    }
    return prev;
}

template<class T>
void LinkedList<T>::setSorted(bool sorted) {
    if(this->sorted == true) this->sorted = sorted;
}

template<class T>
int LinkedList<T>::determineIndex(T target) {
    int pos = 0;
    Node<T>* newHead = head;
    bool found = false;
    while(newHead != nullptr) {
        if(target == newHead->data) {
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
int LinkedList<T>::determineIndexNode(Node<T> *target) {
    int pos = 0;
    Node<T>* newHead = head;
    bool found = false;
    while(newHead != nullptr) {
        if(target == newHead) {
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
bool LinkedList<T>::update(T oldValue, T newValue) {
    Node<T> *p = find(oldValue);
    if(p == nullptr) return false;
    p->data = newValue;
}

template<class T>
LinkedList<T> LinkedList<T>::copy() {
    LinkedList<T> newLinkedList(sorted);
    Node<T> *newHead = head;
    while(newHead != nullptr) {
        newLinkedList.insert(newHead->data);
        newHead = newHead->next;
    }
    return newLinkedList;
}

template<class T>
void LinkedList<T>::operator=(const LinkedList &linkedList) {
    clear();
    this = linkedList;
}

template<class T>
T &LinkedList<T>::operator[](int idx) {
    int counter = 0;
    Node<T> *newHead = head;
    while(newHead != nullptr) {
        if(idx == counter) return newHead->data;
        newHead = newHead->next;
        counter++;
    }
    return -1;
}

template <class T>
int LinkedList<T>::count() {
    int counter = 0;
    Node<T>* newHead = head;
    while(newHead != nullptr) {
        newHead = newHead->next;
        ++counter;
    }
    return counter;
}

template <class T>
void LinkedList<T>::clear() {
    Node<T>* p;
    while(head != nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
    head = tail = nullptr;
    setSorted(false);
}

template <class T>
LinkedList<T> LinkedList<T>::getSubList(T rangeFirst, T rangeLast, bool remove) {
    //Unfinished
}

template <class T>
LinkedList<T> LinkedList<T>::getSubListNode(Node<T> *rangeFirst, Node<T> *rangeLast, bool remove) {
    //Unfinished
}

/* Private Members */
template <class T>
void LinkedList<T>::insertNode(Node<T>* p, Node<T>* prev) {
    if(head == nullptr) {
        p->next = nullptr;
        head = tail = p;
    } else if(prev == nullptr) {
        p->next = head;
        head = p;
    } else {
        p->next = prev->next;
        prev->next = p;
        if(tail == prev) tail = p;
    }
}

template <class T>
Node<T>* LinkedList<T>::deleteNode(Node<T>* prev) {
    Node<T> *p;
    if(prev == nullptr) {
        p = head;
        head = head->next;
    } else if(head == tail) {
        p = head;
    } else {
        p = prev->next;
        prev->next = p->next;
        if(p == tail) tail = prev;
    }
    return p;
}

template <class T>
Node<T>* LinkedList<T>::insertionSlot(Node<T>* p) {
    Node<T> *prev = nullptr, *newHead = head;
    while(newHead != nullptr) {
        if(newHead->data > p->data) break;
        prev = newHead;
        newHead = newHead->next;
    }
    return prev;
}

template <class T>
bool LinkedList<T>::nodeToDelete(T targetData, Node<T>* &prev) {
    Node<T>* newHead = head;
    prev = nullptr;
    while(newHead != nullptr) {
        if(newHead->data == targetData) return true;
        prev = newHead;
        newHead = newHead->next;
    }
    return false;
}