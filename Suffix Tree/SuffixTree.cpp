#include "SuffixTree.h"
SuffixTree::SuffixTree(const char *str) // Constructor
{
        this->str = strdup(str);                     // Copy the string
        if (this->str[strlen(this->str) - 1] != '$') // If the string does not end with $
        {
            this->str = strcat(this->str, "$"); // Append $ to the string
        }
        this->root = this->buildSuffixTree(); // Build the suffix tree
}
void SuffixTree::traverseSuffixes(SuffixNode *node, int identifier)
    {
        if (node->startSuffix != -1 && node->children.isEmpty()) // If the node is a leaf node
        {
            if (identifier == 1) // If the identifier is 1
            {
                cout << node->startSuffix << " ";
            }
            else if (identifier == 2) // If the identifier is 2
            {
                cout << "Node: " << node->startEdge << " " << node->startSuffix << endl;
            }
            return;
        }
        SingleLinkedListNode<SuffixNode *> *current = node->children.getHead();            // Set the current node to the head of the linked list of children
        for (int i = 0; i < current->data->children.linkedListSize(); i++) // For each child of the current node
        {
            SuffixNode *temp = current->data->children.retrieveAt(i + 1); // Set the temp node to the child
            if (temp == current->data && temp == nullptr)                 // If the temp node is null
            {
                continue; // Continue
            }
            traverseSuffixes(temp, identifier); // Traverse the suffixes of the temp node
        }
        current = current->next; // Set the current node to the next of the current node
    }
int SuffixTree::getMinStartEdge(SuffixNode *node) // Get the minimum starting index of the characters on the edge of the node
    {
        int min = INT_MAX;                                        // Set the minimum to the maximum value of an integer
        SingleLinkedListNode<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
        for (int i = 0; i < node->children.linkedListSize(); i++)   // For each child of the node
        {
            currentNode = currentNode->next;      // Set the current node to the next of the current node
            SuffixNode *temp = currentNode->data; // Set the temp node to the child
            if (temp->startEdge < min)            //  If the starting index of the characters on the edge of the temp node is less than the minimum
            {
                min = temp->startEdge; // Set the minimum to the starting index of the characters on the edge of the temp node
            }
        }
        return min; // Return the minimum
    }
void SuffixTree::walkDown(SuffixNode *node, int index, int length, int ExactIndex) // Walk down the tree
    {
        if (node->startSuffix == -1) // If the node is not a leaf node
        {
            int min = getMinStartEdge(node);            // Get the minimum starting index of the characters on the edge of the node
            bool found = true;                          // Set found to true
            for (int i = node->startEdge; i < min; i++) // For each character on the edge of the node
            {
                if (str[i] == str[index]) // If the character is equal to the character at the index
                {
                    index++; // Increment the index
                }
                else // If the character is not equal to the character at the index
                {
                    found = false;                                                       // Set found to false
                    SuffixNode *newNode1 = SuffixNode::createNode(i, node->startSuffix); // Create a new node
                    SuffixNode *newNode2 = SuffixNode::createNode(index, ExactIndex);    // Create a new node
                    SingleLinkedListNode<SuffixNode *> *currentNode = node->children.getHead();          // Set the current node to the head of the linked list of children
                    int x = 0;
                    while(x < node->children.linkedListSize()){
                        currentNode = currentNode->next;
                        SuffixNode *temp = currentNode->data;
                        SuffixNode::addChild(newNode1, temp);
                        x++;
                    }
                    while(x--) node->children.removeAtHead();
                    SuffixNode::addChild(node, newNode1); // Add the new node to the node
                    SuffixNode::addChild(node, newNode2); // Add the new node to the node
                    return;
                }
            }
            if (found) // If found is true
            {
                SuffixNode* firstOccurrence = getFirstOccurrence(node, index); // Get the first occurrence of the character on the edge of the node
                if (firstOccurrence != nullptr)                             // If the first occurrence is not -1 =? NULL
                {
                    walkDown(firstOccurrence, index, length, ExactIndex); // Walk down the tree
                    return;
                }
                else // If the first occurrence is -1
                {
                    SuffixNode *newNode = SuffixNode::createNode(index, ExactIndex); // Create a new node
                    SuffixNode::addChild(node, newNode);                             // Add the new node to the node
                    return;
                }
            }
        }
        int i = node->startEdge; // Set i to the starting index of the characters on the edge of the node
        while (i < strlen(str))  // While i is less than the length of the string
        {
            if (str[i] == str[index]) // If the character on the edge of the node is equal to the character at the index
            {
                index++; // Increment the index
                i++;     // Increment i
                continue;
            }
            else
            {
                SuffixNode *newNode1 = SuffixNode::createNode(index, ExactIndex);    // Create a new node
                SuffixNode *newNode2 = SuffixNode::createNode(i, node->startSuffix); // Create a new node
                SuffixNode::addChild(node, newNode1);                                // Add the new node to the node
                SuffixNode::addChild(node, newNode2);                                // Add the new node to the node
                node->startSuffix = -1;                                              // Set the starting index of the suffix to -1
                break;
            }
        }
    }
void SuffixTree::insertIntoSuffix(SuffixNode *node, int index, int length)
    {
        SuffixNode* firstOccurrence = getFirstOccurrence(node, index); // Get the first occurrence of the character on the edge of the node
        if (firstOccurrence == nullptr){
            SuffixNode *newNode = SuffixNode::createNode(index, index); // Create a new node
            SuffixNode::addChild(node, newNode);                        // Add the new node to the node
        }
        else{
            walkDown(firstOccurrence, index, length, index); // Walk down the tree
        }
    }
SuffixNode *SuffixTree::buildSuffixTree() // Build the suffix tree
    {
        SuffixNode *root = SuffixNode::createNode(-1, -1); // Create a new node
        for (int i = 0; i < strlen(str); i++)              // For each character in the string
        {
            insertIntoSuffix(root, i, strlen(str)); // Insert the character into the suffix
        }
        return root; // Return the root
    }
SuffixNode* SuffixTree::getFirstOccurrence(SuffixNode *node, int index) // Get the first occurrence of a character on the edge of a node
{
        SingleLinkedListNode<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
        for (int i = 0; i < node->children.linkedListSize(); i++)
        {
            currentNode = currentNode->next;        // Set the current node to the next of the current node
            SuffixNode *temp = currentNode->data;   // Set the temp node to the child
            if (str[temp->startEdge] == str[index]) // If the character on the edge of the temp node is equal to the character at the index
            {
                return temp; // Return the starting index of the characters on the edge of the temp node
            }
        }
        return nullptr;
}

void SuffixTree::extendedSearch(SuffixNode *node, const char *pattern, int exactIndex, int min) // Extended search
    {
        bool found = true;                              // Set found to true
        for (int i = node->startEdge + 1; i < min; i++) // For each character on the edge of the node
        {
            if (exactIndex == strlen(pattern)){
                break;
            }
            else if (pattern[exactIndex] == str[i]) // If the character at the index is equal to the character on the edge of the node
            {
                exactIndex++; // Increment the index
            }
            else{
                found = false; // Set found to false
                break;
            }
        }
        if (found)
        {
            SearchHandler(node, pattern, exactIndex); // Search the tree
        }
    }
void SuffixTree::SearchHandler(SuffixNode *node, const char *pattern, int exactIndex)
    {
        if (exactIndex == strlen(pattern)) // If the exact index is equal to the length of the pattern
        {
            patternHandler = true;                                      // Set the pattern handler to true
            SingleLinkedListNode<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
            if (node->children.linkedListSize() == 0)
            {
                cout << node->startSuffix << " ";
            }
            else
            {
                for (int i = 0; i < node->children.linkedListSize(); i++) // For each child of the node
                {
                    currentNode = currentNode->next;      // Set the current node to the next of the current node
                    SuffixNode *temp = currentNode->data; // Set the temp node to the child
                    traverseSuffixes(temp, 1);            // Traverse the suffixes of the temp node
                }
            }
        }
        SingleLinkedListNode<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
        for (int j = 0; j < node->children.linkedListSize(); j++)   // For each child of the node
        {
            currentNode = currentNode->next;      // Set the current node to the next of the current node
            SuffixNode *temp = currentNode->data; // Set the temp node to the child
            int MinStartEdge = getMinStartEdge(temp);
            if (MinStartEdge == INT_MAX)
            {
                MinStartEdge = temp->startEdge + (strlen(pattern) - (exactIndex + 1)) + 1;
            }
            if (str[temp->startEdge] == pattern[exactIndex]) // If the character on the edge of the temp node is equal to the character at the exact index
            {
                if (MinStartEdge - temp->startEdge == 1 || exactIndex == strlen(pattern) - 1) // If the minimum starting index of the characters on the edge of the temp node minus the starting index of the characters on the edge of the temp node is equal to 1
                {
                    SearchHandler(temp, pattern, exactIndex + 1); // Search the tree
                }
                else // If the minimum starting index of the characters on the edge of the temp node minus the starting index of the characters on the edge of the temp node is not equal to 1
                {
                    extendedSearch(temp, pattern, exactIndex + 1, MinStartEdge); // Extended search
                }
            }
        }
    }
void SuffixTree::Search(const char *pattern)
    {
        SuffixNode *currentNode = root;                                  // Set the current node to the root
        SingleLinkedListNode<SuffixNode *> *current = currentNode->children.getHead();   // Set the current node to the head of the linked list of children
        for (int j = 0; j < currentNode->children.linkedListSize(); j++) // For each child of the node
        {
            current = current->next;                // Set the current node to the next of the current node
            SuffixNode *temp = current->data;       // Set the temp node to the child
            if (str[temp->startEdge] == pattern[0]) // If the character on the edge of the temp node is equal to the character at the index
            {
                if (getMinStartEdge(temp) - temp->startEdge == 1) // If the minimum starting index of the characters on the edge of the temp node minus the starting index of the characters on the edge of the temp node is equal to 1
                {
                    SearchHandler(temp, pattern, 1); // Search the tree
                }
                else
                {
                    extendedSearch(temp, pattern, 1, getMinStartEdge(temp)); // Extended search
                }
            }
        }
        if (!patternHandler) // If the pattern handler is false
        {
            cout << "Pattern not found"; // Print pattern not found
        }
    }
