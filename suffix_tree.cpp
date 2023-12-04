#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * Node Class
 * Represents a node in the suffix tree
*/
struct  Node {
    
    Node* children;  // Linked list of children nodes
    int startEdge;   // Starting index of characters on the edge going to this node
    int startSuffix; // Starting index of the suffix ending at this node (used for leaf nodes only)

    /**
     * Create a new Node object.
     *
     * @param startEdge the starting edge of the node
     * @param startSuffix the starting suffix of the node
     *
     * @return a pointer to the newly created Node object
     *
     */
    static Node* createNode(int startEdge = -1, int startSuffix = -1) {
        Node* node = new Node; // Create a new Node object
        node->children = nullptr; // Set the children pointer to nullptr
        node->startEdge = startEdge; // Set the startEdge property of the node
        node->startSuffix = startSuffix; // Set the startSuffix property of the node
        return node; // Return a pointer to the newly created Node object
    }
};
