#include "IntervalNode.h"

IntervalNode::IntervalNode(int lowerBound, int upperBound) {
        this->lowerBound = lowerBound;
        this-> upperBound = upperBound;
        this->max = upperBound;
        this->left = nullptr;
        this->right = nullptr;
}

IntervalNode::IntervalNode() {
        this->left = nullptr;
        this->right = nullptr;
}