#include "SingleLinkedList.h"

template <typename T>
SingleLinkedListNode<T> *SingleLinkedList<T>::getHead()
{
    return head;
}


template <typename T>
SingleLinkedList<T>::SingleLinkedList()
{
    head = nullptr;
    tail = nullptr;
    len = 0;
}

template <typename T>
void SingleLinkedList<T>::insertAtTail(T data)
{
    SingleLinkedListNode<T> *Newitem = new SingleLinkedListNode<T>(data);
    if (head == nullptr)
    {
        tail = Newitem;
        head = Newitem;
        return;
    }
    len += 1;
    tail->next = Newitem;
    tail = Newitem;
}
template <typename T>
void SingleLinkedList<T>::removeAtHead()
{
    if (head == NULL) // If the list is empty
    {
        cout << "List Empty " << endl;
        return;
    }
    len--;                         // Decrement the length
    SingleLinkedListNode<T> *Newitem = head->next; // Set the new head to the next of the current head
    head->next = Newitem->next;    // Set the next of the current head to the next of the new head
    if (len == 0)                  // If the list is empty
    {
        tail = head; // Set the tail to the head
    }
    delete Newitem; // Delete the new head
}

template <typename T>
T SingleLinkedList<T>::retrieveAt(int index)
{
    if (index > len || index < 0)
    { // If the index is out of range
        cout << "Index out of range" << endl;
        return 0;
    }
    else if (len == 0) // If the list is empty
    {
        cout << "List Empty" << endl;
        return 0;
    }
    else
    {
        SingleLinkedListNode<T> *Newitem = head; // Set the new node to the head
        while (index != 0 && Newitem->next != NULL)
        {
            Newitem = Newitem->next; // Set the new node to the next of the new node
            index--;                 // Decrement the index
        }
        return (Newitem->data); // Return the data of the new node
    }
}

template <typename T>
int SingleLinkedList<T>::isEmpty()
{
    return (linkedListSize() == 0); // Return if the length is 0
}

template <typename T>
int SingleLinkedList<T>::linkedListSize()
{
    return len - 1 == -1 ? 0 : len; // Return the length
}
