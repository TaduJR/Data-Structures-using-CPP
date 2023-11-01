//
// Created by Natu on 4/29/2022.
//

#ifndef EXAMLINKEDLIST_LINKEDLIST_H
#define EXAMLINKEDLIST_LINKEDLIST_H

template <class T>
struct Node {
    T data;
    Node <T> *next;  //holds the address of another node
};

template <class T>
class LinkedList {
public:
    LinkedList();
    explicit LinkedList(bool sorted);
    LinkedList(const LinkedList &linkedList);
    virtual ~ LinkedList();
    bool isEmpty();

    void insertFirst(T data);
    void insertBack(T data);
    bool insertBefore(T before, T data);
    bool insertAfter(T after, T data);
    void insertRangeBefore(T before, LinkedList<T> range);
    void insertRangeAfter(T after, LinkedList<T> range);
    void insertRangeBeforeNode(Node<T>* before, LinkedList<T> range);
    void insertRangeAfterNode(Node<T>* after, LinkedList<T> range);
    bool insert(T newData);

    bool removeFirst();
    bool removeLast();
    bool removeRange(T rangeFirst, T rangeLast);
    bool removeRangeNode(Node<T>* rangeFirst, Node<T>* rangeLast);
    bool remove(T targetData);

    bool update(T oldValue, T newValue);
    LinkedList<T> copy();
    void setSorted(bool sorted);
    void operator = (const LinkedList &linkedList);
    T& operator [] (int idx);
    LinkedList getSubList(T rangeFirst, T rangeLast, bool remove = true);
    LinkedList getSubListNode(Node<T>* rangeFirst, Node<T>* rangeLast, bool remove = true);

    Node<T>* find(T target);
    Node<T>* findNode(Node<T>* target);
    Node<T>* determinePrev(T target);
    Node<T>* determinePrevNode(Node<T>* target);
    Node<T>* determineTailPrev();
    int determineIndex(T target);
    int determineIndexNode(Node<T> *target);

    int count();
    void clear();
    void sort();
    void displayForward(void (*displayer)(T));
    void displayBackward(void (*displayer)(T));
private:
    Node<T> *head;
    Node<T> *tail;
    bool sorted;
    void insertNode(Node<T> * p, Node<T> * prev);
    Node<T> * deleteNode(Node<T> *prev);
    Node<T> * insertionSlot(Node<T> * p); //it finds after which to insert
    bool nodeToDelete(T  targetData, Node<T> * & prev);
};

#endif //EXAMLINKEDLIST_LINKEDLIST_H
