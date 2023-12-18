#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include "SuffixNode/SuffixNode.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

class SuffixTree
{
private:
    SuffixNode *root;
    char *str;
    bool patternHandler = false;

public:
    explicit SuffixTree(const char *str);
    void traverseSuffixes(SuffixNode *node, int identifier = 2);
    int getMinStartEdge(SuffixNode *node); // Get the minimum starting index of the characters on the edge of the node
    void walkDown(SuffixNode *node, int index, int length, int ExactIndex);
    void insertIntoSuffix(SuffixNode *node, int index, int length);
    SuffixNode *buildSuffixTree();
    SuffixNode *getFirstOccurrence(SuffixNode *node, int index);
    void extendedSearch(SuffixNode *node, const char *pattern, int exactIndex, int min);
    void SearchHandler(SuffixNode *node, const char *pattern, int exactIndex);
    void Search(const char *pattern);
};
#endif //SUFFIX_TREE_H
