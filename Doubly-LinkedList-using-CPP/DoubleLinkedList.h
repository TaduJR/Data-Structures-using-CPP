//
// Created by Natu on 4/30/2022.
//

#ifndef EXAMDOUBLYLINKEDLIST_DOUBLELINKEDLIST_H
#define EXAMDOUBLYLINKEDLIST_DOUBLELINKEDLIST_H

template <class T>
struct DNode {
    T data;
    DNode<T> *next;
    DNode<T> *prev;
};

template <class T>
class DLinkedList {
public:
    DLinkedList(); //constructor
    explicit DLinkedList(bool sorted);//constructor
    DLinkedList(const DLinkedList &newDLinkedList); //copy constructor
    virtual ~DLinkedList(); //destructor
    bool isEmpty(); //returns true if list is empty

    void insertFirst(T data);
    void insertBack(T data);
    bool insertBefore(T before, T data);
    bool insertAfter(T after, T data);
    void insertRangeBeforeNode(DNode<T>* before, DLinkedList<T> range);
    void insertRangeAfterNode(DNode<T>* after, DLinkedList<T> range);
    void insertRangeBefore(T before, DLinkedList<T> range);
    void insertRangeAfter(T after, DLinkedList<T> range);
    bool insert(T newData);

    bool removeFirst();
    bool removeLast();
    bool removeRange(T rangeFirst, T rangeLast);
    bool removeRangeNode(DNode<T>* rangeFirst, DNode<T>* rangeLast);
    bool remove(T targetData);

    bool update(T oldValue, T newValue);
    DNode<T>* find(T target);
    DNode<T>* findNode(DNode<T>* target);
    int determineIndex(T target);
    int determineIndexNode(DNode<T> *target);

    int count();
    void clear();

    DLinkedList<T> copy();
    void setSorted(bool sorted);
    void operator = (const DLinkedList &linkedList);
    T& operator [] (int idx);

    void displayForward(void (*displayer)(T));
    void displayBackward(void (*displayer)(T));
    void sort();
    DLinkedList getSubList(T rangeFirst, T rangeLast, bool remove = true);
    DLinkedList getSubListNode(DNode<T>* rangeFirst, DNode<T>* rangeLast, bool remove = true);
private:
    DNode<T> * head;
    DNode<T> * tail;
    bool sorted;
    void insertNode(DNode<T> *p, DNode<T> *prev);
    DNode<T> *  deleteNode(DNode<T> *prev); //remove node
    DNode<T> * insertionSlot(DNode<T> * p);//it finds after which to insert
    bool nodeToDelete(T targetData, DNode<T>* &prev);
};

#endif //EXAMDOUBLYLINKEDLIST_DOUBLELINKEDLIST_H
