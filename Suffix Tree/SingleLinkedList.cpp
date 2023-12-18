#include <iostream>
using namespace std;
template <typename T>
class Node
{
public:
    Node *next; // Pointer to next node
    T data;     // Data stored in the node
    Node(T data)
    {
        this->data = data; // Initialize the data
        this->next = NULL; // Point to NULL
    }
};

template <typename T>
class SingleLinkedList
{
private:
    Node<T> *head; // Pointer to head node
    Node<T> *tail; // Pointer to tail node
    int len = 0;   // Length of the linked list
public:
    Node<T> *getHead() // Getter O(1)
    {
        return head;
    }
    void setHead(Node<T> *head) // Setter O(1)
    {
        this->head = head;
    }
    SingleLinkedList() // Constructor O(1)
    {
        head = NULL;
        tail = NULL;
    }
    void insertAtTail(T data) // Insert at tail O(1)
    {
        Node<T> *Newitem = new Node<T>(data); // Create a new node
        if (head == NULL)                     // If the list is empty
        {
            tail = Newitem; // Set the tail to the new node
            head = Newitem; // Set the head to the new node
            return;
        }
        len += 1;             // Increment the length
        tail->next = Newitem; // Set the next of the tail to the new node
        tail = Newitem;       // Set the tail to the new node
    }
    void removeAtHead() // Remove at head O(1)
    {
        if (head == NULL) // If the list is empty
        {
            cout << "List Empty " << endl;
            return;
        }
        len--;                         // Decrement the length
        Node<T> *Newitem = head->next; // Set the new head to the next of the current head
        head->next = Newitem->next;    // Set the next of the current head to the next of the new head
        if (len == 0)                  // If the list is empty
        {
            tail = head; // Set the tail to the head
        }
        delete Newitem; // Delete the new head
    }
    T retrieveAt(int index) // Retrieve at index O(n)
    {
        if (index > len || index < 0)
        { // If the index is out of range
            throw out_of_range("Index out of range");
        }
        else if (len == 0) // If the list is empty
        {
            throw invalid_argument("LinkedList Empty");
        }
        else
        {
            Node<T> *Newitem = head; // Set the new node to the head
            while (index != 0 && Newitem->next != NULL)
            {
                Newitem = Newitem->next; // Set the new node to the next of the new node
                index--;                 // Decrement the index
            }
            return (Newitem->data); // Return the data of the new node
        }
    }
    int isEmpty() // Check if the list is empty O(1)
    {
        return (linkedListSize() == 0); // Return if the length is 0
    }
    int linkedListSize() // Return the length of the linked list O(1)
    {
        return len - 1 == -1 ? 0 : len; // Return the length
    }
};