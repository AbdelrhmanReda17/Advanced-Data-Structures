#ifndef INTERVALNODE_H
#define INTERVALNODE_H

struct IntervalNode {
    int lowerBound;
    int upperBound;
    int max;
    IntervalNode *left;
    IntervalNode *right;
    IntervalNode();
    IntervalNode(int lowerBound, int upperBound);
};

#endif