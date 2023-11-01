//
// Created by Natu on 4/14/2022.
//

#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H

#include <iostream>
struct MemoryException : public std::exception{
    const char * what () {
        return "Unable to allocate memory for a stack node!";
    }
};

struct EmptyStackException: public std::exception{
    const char * what () {
        return "Popping an empty stack!";
    }
};
template <class T>
struct nodeStack {
    T data;
    nodeStack<T> * next;
};
template <class T>
class Stack
{
public:
    Stack();
    virtual ~Stack();
    void push(T data);
    T pop();
    T peep(){ return top->data; };
    bool isEmpty(){ return count == 0; };
    int getCount(){ return count; };
    void empty();
protected:
private:
    nodeStack<T> * top;
    int count;
};

#endif //CALCULATOR_STACK_H
