#include "SingleLinkedListNode.h"

// Node implementation
template <typename T>
SingleLinkedListNode<T>::SingleLinkedListNode(T data)
{
    this->data = data;
    this->next = nullptr;
}
