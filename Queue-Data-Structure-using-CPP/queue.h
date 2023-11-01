//
// Created by Natu on 5/13/2022.
//

#include <iostream>
#include <exception>

#ifndef QUEUEPOINTERIMP_QUEUE_H
#define QUEUEPOINTERIMP_QUEUE_H

template <class T>
struct nodeQueue {
    T data;
    nodeQueue * next;
};

struct MemoryException: public std::exception{
    const char * what () {
        return "Unable to allocate memory for the queue!";
    }
};

struct EmptyQueueException: public std::exception {
    const char * what() {
        return "Dequing an empty queue!";
    }
};

template <class T>
class Queue {
public:
    Queue();
    virtual ~Queue();
    bool isEmpty(){ return front == nullptr; }
    bool enQueue(T data);
    bool peepFront();
    bool peepBack();
    T deQueue();
    int getCount(){ return count; }
    void empty();
protected:
private:
    nodeQueue<T> * front;
    nodeQueue<T> * rear;
    int count;
};

#endif //QUEUEPOINTERIMP_QUEUE_H
