#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "SingleLinkedList.cpp"
using namespace std;

struct SuffixNode
{
    SingleLinkedList<SuffixNode *> children;                      // Linked list of children nodes
    int startEdge;                                                // Starting index of characters on the edge going to this node
    int startSuffix;                                              // Starting index of the suffix ending at this node (used for leaf nodes only)
    static SuffixNode *createNode(int startEdge, int startSuffix) // Create a new suffix node
    {
        SuffixNode *node = new SuffixNode;                 // Create a new node
        node->startEdge = startEdge;                       // Set the starting index of the characters on the edge
        node->startSuffix = startSuffix;                   // Set the starting index of the suffix
        node->children = SingleLinkedList<SuffixNode *>(); // Initialize the linked list of children
        node->children.insertAtTail(node);                 // Insert the node into the linked list of children
        return node;                                       // Return the node
    }

    static void addChild(SuffixNode *parent, SuffixNode *child) // Add a child to a parent node
    {
        parent->children.insertAtTail(child); // Insert the child into the linked list of children of the parent
    }
};
class SuffixTree
{
private:
    SuffixNode *root;
    char *str;
    bool patternHandler = false;

public:
    SuffixTree(const char *str) // Constructor
    {
        this->str = strdup(str);                     // Copy the string
        if (this->str[strlen(this->str) - 1] != '$') // If the string does not end with $
        {
            this->str = strcat(this->str, "$"); // Append $ to the string
        }
        this->root = this->buildSuffixTree(this->str); // Build the suffix tree
    }
    void traverseSuffixes(SuffixNode *node, int identifier = 2)
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
        Node<SuffixNode *> *current = node->children.getHead();            // Set the current node to the head of the linked list of children
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
    int getMinStartEdge(SuffixNode *node) // Get the minimum starting index of the characters on the edge of the node
    {
        int min = INT16_MAX;                                        // Set the minimum to the maximum value of an integer
        Node<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
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
    void walkDown(SuffixNode *node, int index, int length, int ExactIndex) // Walk down the tree
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
                    Node<SuffixNode *> *currentNode = node->children.getHead();          // Set the current node to the head of the linked list of children
                    int x = 0;                                                           // Set x to 0
                    for (int j = 0; j < node->children.linkedListSize(); j++)            // For each child of the node
                    {
                        currentNode = currentNode->next;      // Set the current node to the next of the current node
                        SuffixNode *temp = currentNode->data; // Set the temp node to the child
                        SuffixNode::addChild(newNode1, temp); // Add the child to the new node
                        x++;                                  // Increment x
                    }
                    for (int j = 0; j < x; j++) // For each child of the node
                    {
                        node->children.removeAtHead(); // Remove the child from the linked list of children of the node
                    }
                    SuffixNode::addChild(node, newNode1); // Add the new node to the node
                    SuffixNode::addChild(node, newNode2); // Add the new node to the node
                    return;
                }
            }
            if (found) // If found is true
            {
                int FirstOccurrence = getFirstOccurrence(node, index); // Get the first occurrence of the character on the edge of the node
                if (FirstOccurrence != -1)                             // If the first occurrence is not -1
                {
                    Node<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
                    for (int i = 0; i < node->children.linkedListSize(); i++)   // For each child of the node
                    {
                        currentNode = currentNode->next;                // Set the current node to the next of the current node
                        SuffixNode *walkDownNode = currentNode->data;   // Set the walk down node to the child
                        if (str[walkDownNode->startEdge] == str[index]) // If the character on the edge of the walk down node is equal to the character at the index
                        {
                            walkDown(walkDownNode, index, length, ExactIndex); // Walk down the tree
                        }
                    }
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
    void insertIntoSuffix(SuffixNode *node, char *str, int index, int length)
    {
        int FirstOccurrence = getFirstOccurrence(node, index); // Get the first occurrence of the character on the edge of the node
        if (FirstOccurrence == -1)
        {
            SuffixNode *newNode = SuffixNode::createNode(index, index); // Create a new node
            SuffixNode::addChild(node, newNode);                        // Add the new node to the node
        }
        else
        {
            Node<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
            for (int i = 0; i < node->children.linkedListSize(); i++)   // For each child of the node
            {
                currentNode = currentNode->next;                // Set the current node to the next of the current node
                SuffixNode *walkDownNode = currentNode->data;   // Set the walk down node to the child
                if (str[walkDownNode->startEdge] == str[index]) // If the character on the edge of the walk down node is equal to the character at the index
                {
                    walkDown(walkDownNode, index, length, index); // Walk down the tree
                    break;
                }
            }
        }
        return;
    }
    SuffixNode *buildSuffixTree(char *str) // Build the suffix tree
    {
        SuffixNode *root = SuffixNode::createNode(-1, -1); // Create a new node
        for (int i = 0; i < strlen(str); i++)              // For each character in the string
        {
            insertIntoSuffix(root, str, i, strlen(str)); // Insert the character into the suffix
        }
        return root; // Return the root
    }
    int getFirstOccurrence(SuffixNode *node, int index) // Get the first occurrence of a character on the edge of a node
    {
        Node<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
        for (int i = 0; i < node->children.linkedListSize(); i++)
        {
            currentNode = currentNode->next;        // Set the current node to the next of the current node
            SuffixNode *temp = currentNode->data;   // Set the temp node to the child
            if (str[temp->startEdge] == str[index]) // If the character on the edge of the temp node is equal to the character at the index
            {
                return temp->startEdge; // Return the starting index of the characters on the edge of the temp node
            }
        }
        return -1;
    }
    SuffixNode *getRoot() // Get the root of the suffix tree
    {
        return root; // Return the root
    }
    void extendedSearch(SuffixNode *node, const char *pattern, int exactIndex, int min) // Extended search
    {
        bool found = true;                              // Set found to true
        for (int i = node->startEdge + 1; i < min; i++) // For each character on the edge of the node
        {
            if (exactIndex == strlen(pattern))
            {
                break;
            }
            if (pattern[exactIndex] == str[i]) // If the character at the index is equal to the character on the edge of the node
            {
                exactIndex++; // Increment the index
            }
            else
            {
                found = false; // Set found to false
                break;
            }
        }
        if (found)
        {
            SearchHandler(node, pattern, exactIndex); // Search the tree
        }
    }
    void SearchHandler(SuffixNode *node, const char *pattern, int exactIndex)
    {
        if (exactIndex == strlen(pattern)) // If the exact index is equal to the length of the pattern
        {
            patternHandler = true;                                      // Set the pattern handler to true
            Node<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
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
        Node<SuffixNode *> *currentNode = node->children.getHead(); // Set the current node to the head of the linked list of children
        for (int j = 0; j < node->children.linkedListSize(); j++)   // For each child of the node
        {
            currentNode = currentNode->next;      // Set the current node to the next of the current node
            SuffixNode *temp = currentNode->data; // Set the temp node to the child
            int MinStartEdge = getMinStartEdge(temp);
            if (MinStartEdge == INT16_MAX)
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
    void Search(const char *pattern)
    {
        SuffixNode *currentNode = root;                                  // Set the current node to the root
        Node<SuffixNode *> *current = currentNode->children.getHead();   // Set the current node to the head of the linked list of children
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
};

int main()
{
    SuffixTree t1("bananabanaba$");
    // t1.traverseSuffixes(t1.getRoot(), 2);
    t1.Search("ana"); // Prints: 1 3 7
    cout << endl;
    t1.Search("naba"); // Prints: 4 8
    cout << endl;
    t1.Search("ban"); // Prints: 0 6
    cout << endl;
    SuffixTree t2("papatpapa$");
    // t2.traverseSuffixes(t2.getRoot(), 2);
    t2.Search("pa"); // Prints: 2 5 0 7
    cout << endl;
    t2.Search("papa"); // Prints: 5 0
    cout << endl;
    t2.Search("pat"); // Prints: 2
    cout << endl;
    SuffixTree t3("papatpapta$");
    // t3.traverseSuffixes(t3.getRoot(), 2);
    t3.Search("pa"); // Prints: 2 5 0
    cout << endl;
    t3.Search("papa"); // Prints: 0
    cout << endl;
    t3.Search("pat"); // Prints: 2
    cout << endl;
    SuffixTree t4("cattcat$");
    // t4.traverseSuffixes(t4.getRoot(), 2);
    t4.Search("cat"); // Prints: 0 4
    cout << endl;
    t4.Search("tcat"); // Prints: 3
    cout << endl;
    t4.Search("at"); // Prints: 1 5
    cout << endl;
    SuffixTree t5("mississippi$");
    // t5.traverseSuffixes(t5.getRoot(), 2);
    t5.Search("iss"); // Prints: 1 4
    cout << endl;
    t5.Search("ss"); // Prints: 2 5
    cout << endl;
    t5.Search("pi"); // Prints: 9
    cout << endl;
    SuffixTree t6("ababaa$");
    // t6.traverseSuffixes(t6.getRoot(), 2);
    t6.Search("aba"); // Prints: 0 2
    cout << endl;
    t6.Search("abaa"); // Prints: 2
    cout << endl;
    t6.Search("ba"); // Prints: 1 3 5
    cout << endl;
    SuffixTree t7("ratatat$");
    // t7.traverseSuffixes(t7.getRoot(), 2);
    t7.Search("rat"); // Prints: 0
    cout << endl;
    t7.Search("ta"); // Prints: 4 2
    cout << endl;
    t7.Search("tata"); // Prints: 2
    cout << endl;
    SuffixTree t8("aaaaaaa$");
    // t8.traverseSuffixes(t8.getRoot(), 2);
    t8.Search("a"); // Prints: 1 0 2 3 4 5 6
    cout << endl;
    t8.Search("aa"); // Prints: 1 0 2 3 4 5
    cout << endl;
    t8.Search("aaa"); // Prints: 1 0 2 3 4
    cout << endl;
    SuffixTree t9("gatagaca$");
    // t9.traverseSuffixes(t9.getRoot(), 2);
    t9.Search("gat"); // Prints: 0
    cout << endl;
    t9.Search("aga"); // Prints: 3
    cout << endl;
    t9.Search("ca"); // Prints: 6
    cout << endl;
    SuffixTree t10("nonsense$");
    // t10.traverseSuffixes(t10.getRoot(), 2);
    t10.Search("non"); // Prints: 0
    cout << endl;
    t10.Search("sen"); // Prints:3
    cout << endl;
    t10.Search("se"); // Prints: 6 3
    cout << endl;
    return 0;
}
