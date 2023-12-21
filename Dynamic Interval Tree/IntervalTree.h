#ifndef DYNAMICINTERVALTREE_H
#define DYNAMICINTERVALTREE_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "IntervalNode/IntervalNode.h"

using namespace std;


class IntervalTree {
    IntervalNode* root = nullptr;
    
    void Print(IntervalNode* root);
    IntervalNode* InsertIntervalHandler(IntervalNode* current, IntervalNode* node);
    IntervalNode* SearchIntervalHandler(IntervalNode* current, const IntervalNode* node);

public:
    void InsertInterval(int lowerBound, int upperBound);
    void SearchInterval(int lowerBound, int upperBound);
    void Print();
};

#endif