#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <typename T>
class SingleLinkedListNode
{
public:
    SingleLinkedListNode *next;
    T data;
    SingleLinkedListNode(T data);
};
#endif // NODE_H