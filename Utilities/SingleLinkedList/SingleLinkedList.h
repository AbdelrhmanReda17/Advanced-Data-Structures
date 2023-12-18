#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H
#include "SingleLinkedListNode.cpp"

template <typename T>
class SingleLinkedList
{
private:
    SingleLinkedListNode<T> *head;
    SingleLinkedListNode<T> *tail;
    int len;
public:
    SingleLinkedListNode<T> *getHead();
    SingleLinkedList();
    void insertAtTail(T data);
    void removeAtHead();
    T retrieveAt(int index);
    int isEmpty();
    int linkedListSize();
};
#endif // SINGLE_LINKED_LIST_H
