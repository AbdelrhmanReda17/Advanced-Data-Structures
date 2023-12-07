#include<bits/stdc++.h>
#define OATHKEEPER ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(x) (x).begin(), (x).end()
#define ll long long
#define yes cout << "YES\n";
#define no cout << "NO\n";
#define endl "\n"
#define fr(x,n,o) for(ll i = x ; i < n ;i+=o)
#define frj(x,n,o) for(ll j = x ; j < n ;j+=o)
#define all(x) (x).begin(), (x).end()
#define in(x,n) for(int i=0;i<(n);i++) cin>>(x)[i]
#define out(x,n) for(int i=0;i<(n);i++) cout<<(x)[i]<<" \n"[i==(n)-1];
using namespace std;
template <typename T>
class Node{
    public:
        Node* next;
        T data;   
    Node(T data)
    {
        this->data = data;
        this->next = NULL;
    }
};

template <typename T>
class SingleLinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int len = 0;
    public:
        Node<T>* getHead(){
            return head;
        }
        void setHead(Node<T>* head){
            this->head = head;
        }
        SingleLinkedList() {
            head = NULL;
            tail = NULL;
        }
        void insertAtTail(T data)        // O(1)
        {
            Node<T>* Newitem = new Node<T>(data);
            if(head == NULL){
                tail = Newitem;
                head = Newitem;
                return;
            }           
            len +=1;
            tail->next = Newitem;
            tail = Newitem;
        }
        void insertAtHead(T data)         // O(1)
        {
            Node<T>* Newitem = new Node<T>(data);
            if(head == NULL){
                tail = Newitem;
                head = Newitem;
                return;
            }
            len +=1;
            Newitem->next = head;
            head = Newitem;
        }
        void insertAt(int index ,T data )         // O(n)
        {
            Node<T>* Newitem = new Node<T>(data);
            if (index == 1){
                insertAtHead(data);
                return;
            }else if(index-1 == len){
                insertAtTail(data);
                return;
            }else if (index > len || index <= 0){
                throw out_of_range("Index out of range");
            }else if(len == 0)
                throw invalid_argument("LinekedList Empty");
            else{
                Node<T>* prv = head;
                int x =1;
                len++;
                while (x != index - 1 ) {
                        prv = prv->next;
                        x++;
                }  
                Newitem->next = prv->next;
                prv->next = Newitem;
            }
        }
        void print() // O(n)
        {
            Node<T>* temp = head;
            if (head == NULL) {
                cout << "List empty" << endl;
                return;
            }
            while (temp != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }cout << endl << "Size Of The linked List : " << len << endl ;
        }
        void removeAt(int index)  // O(n)
        {   index++;
            if(len == 0){
                throw invalid_argument("LinekedList Empty");
            }
            if (index == 1){
                removeAtHead();
                return;
            }else if(index-1 == len){
                removeAtTail();
                return;
            }else if (index > len || index <= 0){
                throw out_of_range("Index out of range");
            }
            else{
                Node<T>* temp;
                Node<T>* prv = head;
                int x = 1;
                len--;
                while (x != index - 1 ) {
                    prv = prv->next;
                    x++;
                }  
                temp = prv->next;
                prv->next = temp->next;
                delete[] temp;                
            }
        }
        void removeAtTail(){  // O(n)
            if(head == NULL)
            {
                cout << "List Empty" << endl;
                return;
            }
            len--;
            Node<T>* Newitem = head;
            while (Newitem->next->next != NULL) {
                Newitem = Newitem->next;
            }            
            delete tail;
            Newitem->next = NULL;
            tail = Newitem;
        }
        void removeAtHead(){  // O(1)
            if(head == NULL)
            {
                cout << "List Empty " << endl;
                return;
            }
            len--;
            Node<T>* Newitem = head->next;
            head->next = Newitem->next;
            if(len == 0) {
                tail = head;
            }
            delete Newitem;
        }
        bool isExist(T data) // O(n)
        {
            if(len == 0 )
                throw invalid_argument("LinkedList Empty");
            Node<T>* Newitem = head;
            while(Newitem->data != data && Newitem->next != NULL)
            {
                Newitem = Newitem->next;
            }
            return (Newitem->data == data);
        }
        T retrieveAt(int index) // O(n)
        {
            if(index > len || index < 0 ){
                throw out_of_range("Index out of range");
            }
            else if (len == 0)
            {
                throw invalid_argument("LinkedList Empty");
            }
            Node<T>* Newitem = head;
            while(index != 0 && Newitem->next != NULL)
            {
                Newitem = Newitem->next;
                index--;
            }
            return (Newitem->data);
        }
        int isItemAtEqual(T data , int index) // O(n)
        {
            if(index > len || index < 0 ){
                throw out_of_range("Index out of range");
            }
            else if (len == 0)
            {
                throw invalid_argument("LinkedList Empty");
            }
            Node<T>* Newitem = head;
            while(Newitem->next != NULL && index > 0)
            {
                Newitem = Newitem->next;
                index--;
            }
            return (Newitem->data == data) ;
        }
        void replaceAt(T data , int index) // O(n)
        {
            Node<T>* Newitem = head;
            while(Newitem->next != NULL && index != 0)
            {
                Newitem = Newitem->next;
                index--;
            }
            Newitem->data = data ;
        }
        int isEmpty(){
            return (linkedListSize() == 0);
        }
        int linkedListSize(){
            return len - 1 == -1 ? 0 : len ;
        }
        void clear(){
            if(len == 0 )
                throw invalid_argument("LinkedList Empty");
            len=0;
            Node<T>* current = head->next;
            while (current != nullptr) {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            }
        }
        void swap(int FirstItemindex, int Seconditemindex) {    //O(n)
                if (FirstItemindex > len || FirstItemindex < 0) {
                    throw out_of_range("Index out of range");
                }
                if (Seconditemindex > len || Seconditemindex < 0) {
                    throw out_of_range("Index out of range");
                }
                if (len == 0) {
                    throw invalid_argument("LinkedList Empty");
                }
                if (FirstItemindex > Seconditemindex) {
                    std::swap(FirstItemindex, Seconditemindex);
                }
                if (FirstItemindex == Seconditemindex) {
                    throw invalid_argument("Cannot Swap same index");
                }
                Node<T>* FirstNode = head;
                Node<T>* SecondNode = head;
                Node<T>* FirstNodePrev = NULL;
                Node<T>* SecondNodePrev = NULL;
                Node<T>* FirstNodeNext = NULL;
                Node<T>* SecondNodeNext = NULL;
                if (FirstItemindex == 0) {
                    FirstNodePrev = NULL;
                } else {
                    while (FirstNode->next != NULL && FirstItemindex > 1) {
                        FirstNode = FirstNode->next;
                        FirstItemindex--;
                    }
                    FirstNodePrev = FirstNode;
                    FirstNode = FirstNode->next;
                }
                if (Seconditemindex == 0) {
                    SecondNodePrev = NULL;
                } else {
                    while (SecondNode->next != NULL && Seconditemindex > 1) {
                        SecondNode = SecondNode->next;
                        Seconditemindex--;
                    }
                    SecondNodePrev = SecondNode;
                    SecondNode = SecondNode->next;
                }
                if (FirstNode == NULL || SecondNode == NULL) {
                    return;
                }
                FirstNodeNext = FirstNode->next;
                SecondNodeNext = SecondNode->next;
                if (FirstNodeNext == SecondNode) { // Adjacent
                    if (FirstNodePrev != NULL) {
                        FirstNodePrev->next = SecondNode;
                    } else {
                        head = SecondNode;
                    }
                    SecondNode->next = FirstNode;
                    FirstNode->next = SecondNodeNext;
                    if (SecondNodeNext == NULL) {
                        tail = FirstNode;
                    }
                    return;
                } else if (SecondNodeNext == FirstNode) { // Adjacent
                    if (SecondNodePrev != NULL) {
                        SecondNodePrev->next = FirstNode;
                    } else {
                        head = FirstNode;
                    }
                    FirstNode->next = SecondNode;
                    SecondNode->next = FirstNodeNext;
                    if (FirstNodeNext == NULL) {
                        tail = SecondNode;
                    }
                    return;
                } else { // Not Adjacent
                    if (FirstNodePrev != NULL) {
                        FirstNodePrev->next = SecondNode;
                    } else {
                        head = SecondNode;
                    }
                    SecondNode->next = FirstNodeNext;
                    if (SecondNodeNext == NULL) {
                        tail = FirstNode;
                    }
                    if (SecondNodePrev != NULL) {
                        SecondNodePrev->next = FirstNode;
                    } else {
                        head = FirstNode;
                    }
                    FirstNode->next = SecondNodeNext;
                    if (FirstNodeNext == NULL) {
                        tail = SecondNode;
                    }
                    return;
                }
            }
    };