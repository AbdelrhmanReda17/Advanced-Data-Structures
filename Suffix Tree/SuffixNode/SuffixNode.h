#ifndef SUFFIX_NODE_H
#define SUFFIX_NODE_H
#include "SingleLinkedList.cpp"

struct SuffixNode
{
    SingleLinkedList<SuffixNode *> children;                      // Linked list of children nodes
    int startEdge;                                                // Starting index of characters on the edge going to this node
    int startSuffix;                                              // Starting index of the suffix ending at this node (used for leaf nodes only)
    static SuffixNode *createNode(int startEdge, int startSuffix); // Create a new suffix node
    static void addChild(SuffixNode *parent, SuffixNode *child); // Add a child to a parent node
};
#endif
