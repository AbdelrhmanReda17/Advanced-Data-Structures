# Suffix Tree 

This is a compact implementation of a Suffix Tree in C++, adhering to specific constraints. The Suffix Tree is constructed according to the requirements outlined in the provided specifications. The implementation includes a Search operation for substrings.

## Folder Structure
- `SuffixTree.cpp`: The main C++ source file containing the implementation of the Suffix Tree.
- `SuffixNode.cpp`: The implementation of the SuffixNode class.
- `SuffixNode.h`: The header file for the SuffixNode class.
- `SuffixTree.h`: The header file for the SuffixTree class.
## Constraints

- The implementation does not use any built-in functions except `<cstdlib>`, `<cstdio>`, `<cstring>`, and `<iostream>`.
- No usage of string class, vector, or anything from STL libraries.
- Tree construction time complexity is O(n^2), and space complexity is O(n).
- Search complexity is O(m + occ), where m is the length of the searched pattern, and occ is the number of occurrences of the pattern inside the string.

## Test Cases
The **SuffixTreeCases()** function in Main.cpp includes **10** test cases, each with at least 3 search patterns. Feel free to modify or add more test cases according to your needs.
