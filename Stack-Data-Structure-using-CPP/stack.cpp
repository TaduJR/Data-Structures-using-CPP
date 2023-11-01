//
// Created by Natu on 4/14/2022.
//

#include "stack.h"

template <class T>
Stack<T>::Stack() {
    top = nullptr;
    count = 0;
}

template <class T>
Stack<T>::~Stack() {
    empty();
};

template <class T>
void Stack<T>::push(T data) {
    nodeStack<T> *p = new nodeStack<T>;
    if(p == nullptr) throw MemoryException();
    p->data = data;
    if(top == nullptr) {
        top = p;
        p->next = nullptr;
    } else {
        p->next = top;
        top = p;
    }
    count++;
};

template <class T>
T Stack<T>::pop() {
    if(top == nullptr) throw EmptyStackException();
    nodeStack<T> *temp = top;
    T returnVal = temp->data;
    top = top->next;
    delete temp;
    count--;
    return returnVal;
};

template <class T>
void Stack<T>::empty() {
    nodeStack<T> *temp = top, *p;
    while(top != nullptr) {
        p = top;
        top = top->next;
        delete p;
    }
    count = 0;
};