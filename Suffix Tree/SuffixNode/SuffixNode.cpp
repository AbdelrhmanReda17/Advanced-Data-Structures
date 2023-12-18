#include "SuffixNode.h"

SuffixNode *SuffixNode::createNode(int startEdge, int startSuffix)
{
    SuffixNode *node = new SuffixNode;                 // Create a new node
    node->startEdge = startEdge;                       // Set the starting index of the characters on the edge
    node->startSuffix = startSuffix;                   // Set the starting index of the suffix
    node->children = SingleLinkedList<SuffixNode *>(); // Initialize the linked list of children
    node->children.insertAtTail(node);                 // Insert the node into the linked list of children
    return node;
}

void SuffixNode::addChild(SuffixNode *parent, SuffixNode *child)
{
    parent->children.insertAtTail(child);
}
