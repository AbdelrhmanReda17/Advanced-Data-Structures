#include "IntervalTree.h"

void IntervalTree::Print(IntervalNode* root) {
    if (root == nullptr) {
            return;
    }
    Print(root->left);
    cout << "["<<  root->lowerBound << "," << root->upperBound << "] ";
    Print(root->right);
}

IntervalNode* IntervalTree::InsertIntervalHandler(IntervalNode* current, IntervalNode* node) {
        if (current == nullptr) return node;
        if (node->lowerBound < current->lowerBound) current->left = InsertIntervalHandler(current->left, node);
        else current->right = InsertIntervalHandler(current->right, node);
        if (current->max < node->upperBound) current->max = node->upperBound;
        return current;
        
}

IntervalNode* IntervalTree::SearchIntervalHandler(IntervalNode* current, const IntervalNode* node) {
    if(current == nullptr) return nullptr;
    if(current->lowerBound <= node->upperBound && node->lowerBound <= current->upperBound) {
        return current;
    }
    if(current->left != nullptr && current->left->max >= node->lowerBound) {
        return SearchIntervalHandler(current->left, node);
    }
    return SearchIntervalHandler(current->right, node);
}

void IntervalTree::InsertInterval(int lowerBound, int upperBound) {
    root = InsertIntervalHandler(root, new IntervalNode(lowerBound, upperBound));
}

void IntervalTree::SearchInterval(int lowerBound, int upperBound) {
    IntervalNode* node = SearchIntervalHandler(root, new IntervalNode(lowerBound, upperBound));
    if(node == nullptr) {
        cout << "No Overlap" << endl;
    } else {
        cout << "Overlaps with [" << node->lowerBound << "," << node->upperBound << "]" << endl;
    }
}

void IntervalTree::Print() {
    Print(root);
    cout << endl;
}