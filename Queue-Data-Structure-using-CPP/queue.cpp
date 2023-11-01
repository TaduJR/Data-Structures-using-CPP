//
// Created by Natu on 5/13/2022.
//

#include "queue.h"

template<class T>
Queue<T>::Queue() {
    front = rear = nullptr;
    count = 0;
}

template<class T>
Queue<T>::~Queue() {
    empty();
}

template<class T>
bool Queue<T>::enQueue(T data) {
    nodeQueue<T> *p = new nodeQueue<T>;
    if(p == nullptr) throw MemoryException();
    p->data = data;
    p->next = nullptr;
    if (isEmpty())
        front = rear = p;
    else {
        rear->next = p;
        rear = p;
    }
    count++;
    return true;
}

template<class T>
T Queue<T>::deQueue() {
    if(isEmpty()) throw EmptyQueueException();
    nodeQueue<T> *p = front;
    T item = front->data;
    if (front == rear) front = rear = nullptr;
    else front = front->next;
    count--;
    delete p;
    return item;
}

template<class T>
void Queue<T>::empty() {
    nodeQueue<T> *p;
    while(front != nullptr) {
        p = front;
        front = front->next;
        delete p;
    }
    count = 0;
}

template<class T>
T Stack<T>::peepFront() {
    if (isEmpty()) throw EmptyStackException();
    return front->data;
}


template<class T>
T Stack<T>::peepBack() {
    if (isEmpty()) throw EmptyStackException();
    return rear->data;
}
