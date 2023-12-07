#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "SingleLinkedList.cpp"
using namespace std;

struct SuffixNode {
    SingleLinkedList<SuffixNode*> children; // Linked list of children nodes
    int startEdge;                          // Starting index of characters on the edge going to this node
    int startSuffix;                        // Starting index of the suffix ending at this node (used for leaf nodes only)

    static SuffixNode* createNode(int startEdge, int startSuffix ) {
        SuffixNode* node = new SuffixNode;
        node->startEdge = startEdge;
        node->startSuffix = startSuffix;
        node->children = SingleLinkedList<SuffixNode*>();
        node->children.insertAtTail(node);
        return node;
    }

    static void addChild(SuffixNode* parent, SuffixNode* child) {
        parent->children.insertAtTail(child);
    }
};

class SuffixTree {
private:
    SuffixNode* root;
    char* str;
public:
    SuffixTree(const char* str) {
        this->str = strdup(str);
        this->root = this->buildSuffixTree(this->str);
    }
    void traverseSuffixes(SuffixNode* node) {
        if (node->startSuffix != -1 && node->children.isEmpty()) {
            cout << "Node: " << node->startEdge << " " << node->startSuffix << endl;
            return;
        }
        Node<SuffixNode*>* current = node->children.getHead(); 
        for(int i = 0; i < current->data->children.linkedListSize(); i++) {
            SuffixNode* temp = current->data->children.retrieveAt(i+1);
            if(temp == current->data && temp == nullptr){
                continue;
            }
            traverseSuffixes(temp);
        }
        current = current->next;
    }
    void traverseSuffix(SuffixNode* node) {
        if (node->startSuffix != -1 && node->children.isEmpty()) {
            cout << node->startSuffix << " ";
            return;
        }
        Node<SuffixNode*>* current = node->children.getHead(); 
        for(int i = 0; i < current->data->children.linkedListSize(); i++) {
            SuffixNode* temp = current->data->children.retrieveAt(i+1);
            if(temp == current->data && temp == nullptr){
                continue;
            }
            traverseSuffix(temp);
        }
        current = current->next;
    }
    SuffixNode* findSuffixNode(SuffixNode* node , int key) {
        for(int i = 0; i < node->children.linkedListSize(); i++) {
            SuffixNode* temp = node->children.retrieveAt(i+1);
            if(temp->startEdge == key){
                return temp;
            }
        }
        return nullptr;
    }
    int getMinLength(SuffixNode* node) {
        int min = INT16_MAX;
        for(int i = 0; i < node->children.linkedListSize(); i++) {
            SuffixNode* temp = node->children.retrieveAt(i+1);
            if(temp->startEdge < min){
                min = temp->startEdge;
            }
        }
        return min;
    }
    void walkDown(SuffixNode* node , int index , int length , int ExactIndex) {
        if(node->startSuffix == -1){
            int min = getMinLength(node);
            bool found = true;
            for(int i = node->startEdge ; i < min ; i++) {
                if(str[i] == str[index]) {
                    index++;
                }else{
                    found = false;
                    SuffixNode* newNode1 = SuffixNode::createNode(i, node->startSuffix );
                    SuffixNode* newNode2 = SuffixNode::createNode(index, ExactIndex );
                    int x = 0;
                    for(int j = 0 ; j < node->children.linkedListSize(); j++) {
                        SuffixNode* temp = node->children.retrieveAt(j+1);
                        SuffixNode::addChild(newNode1, temp);
                        x++;
                    }
                    for(int j = 0 ; j < x; j++) {
                        node->children.removeAtHead();
                    }
                    SuffixNode::addChild(node, newNode1);
                    SuffixNode::addChild(node, newNode2);
                    return;
                }
            }
            if(found){
                int FirstOccurrence = getFirstOccurrence(node ,  index );
                if (FirstOccurrence != -1) {
                    for(int i = 0 ; i < node -> children.linkedListSize(); i++) {
                        SuffixNode* walkDownNode = node->children.retrieveAt(i+1);
                        if(str[walkDownNode->startEdge] == str[index]){
                            walkDown(walkDownNode , index  , length , ExactIndex);
                        }
                    }
                    return;
                }else{
                    SuffixNode* newNode = SuffixNode::createNode(index, ExactIndex);
                    SuffixNode::addChild(node, newNode);
                    return;
                }
            }
        }
        int i = node->startEdge;
        while(i < strlen(str)) {
            if(str[i] == str[index]) {
                index++;
                i++;
                continue;
            }else{
                SuffixNode* newNode1 = SuffixNode::createNode(index , ExactIndex );
                SuffixNode* newNode2 = SuffixNode::createNode(i, node->startSuffix);
                SuffixNode::addChild(node, newNode1);
                SuffixNode::addChild(node, newNode2);
                node->startSuffix = -1;
                break;
            }
        }
    }
    void insertIntoSuffix(SuffixNode* node, char* str , int index, int length ) {
        int FirstOccurrence = getFirstOccurrence(node, index );
        if (FirstOccurrence == -1) {
            SuffixNode* newNode = SuffixNode::createNode(index, index);
            SuffixNode::addChild(node, newNode);
        }else{
            for(int i = 0 ; i < node -> children.linkedListSize(); i++) {
                SuffixNode* walkDownNode = node->children.retrieveAt(i+1);
                if(str[walkDownNode->startEdge] == str[index]){
                    walkDown(walkDownNode , index , length , index);
                    break;
                }
            }
        }
        return;
    }
    SuffixNode* buildSuffixTree(char* str) {
        SuffixNode* root = SuffixNode::createNode(-1, -1);
        for (int i = 0; i < strlen(str); i++) {
            insertIntoSuffix(root,str,i,strlen(str));
        }
        return root;
    }
    int getFirstOccurrence(SuffixNode* node , int index) {
        for(int i = 0 ; i < node->children.linkedListSize(); i++) {
            SuffixNode* temp = node->children.retrieveAt(i+1);
            if(str[temp->startEdge] == str[index]) {
                return temp->startEdge;
            }
        }
        return -1;
    }
    SuffixNode* getRoot() {
        return root;
    }
    void SearchHandler(SuffixNode* node , const char* pattern , int exactIndex) {
        if(exactIndex == strlen(pattern)) {
            for(int i = 0 ; i < node->children.linkedListSize(); i++) {
                SuffixNode* temp = node->children.retrieveAt(i+1);
                traverseSuffix(temp);
            }
        }
        for (int j = 0; j < node->children.linkedListSize(); j++) {
            SuffixNode* temp = node->children.retrieveAt(j+1);
            int min = getMinLength(temp);
            if(str[temp->startEdge] == pattern[exactIndex]) {
                if(min - temp->startEdge == 1 ){ 
                    SearchHandler(temp, pattern, exactIndex + 1);
                }else{
                    int index = exactIndex + 1;
                    bool found = true;
                    for(int i = temp->startEdge + 1; i < min; i++) {
                        if(pattern[index] == str[i]) {
                            index++;
                        }else{
                            found = false;
                            break;
                        }
                    }
                    if(found) {
                        SearchHandler(temp, pattern, index);
                    }
                }
            }
        }
    }
    void Search(const char* pattern) {
        SuffixNode* currentNode = root;
        for (int j = 0; j < currentNode->children.linkedListSize(); j++) {
            SuffixNode* temp = currentNode->children.retrieveAt(j+1);
            int min = getMinLength(temp);
            if(str[temp->startEdge] == pattern[0]) {
                if(min - temp->startEdge == 1 ){ 
                    SearchHandler(temp, pattern, 1);
                }else{
                    int index = 1;
                    bool found = true;
                    for(int i = temp->startEdge + 1; i < min; i++) {
                        if(pattern[index] == str[i]) {
                            index++;
                        }else{
                            found = false;
                            break;
                        }
                    }
                    if(found) {
                        SearchHandler(temp, pattern, index);
                    }
                }
            }
        }
    }
};

int main() {
    SuffixTree st("bananabanaba$");
    // st.traverseSuffixes(st.getRoot());
    st.Search("naba");
    return 0;
}
