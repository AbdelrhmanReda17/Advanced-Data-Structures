# Suffix Tree 

This is a compact implementation of a Suffix Tree in C++, adhering to specific constraints. The Suffix Tree is constructed according to the requirements outlined in the provided specifications. The implementation includes a Search operation for substrings.

## Project Structure
- `suffix_tree.cpp`: The main C++ source file containing the implementation of the Suffix Tree.
- `CodingStyle.pdf`: A document specifying the coding style guidelines to be followed.
## Constraints

- The implementation does not use any built-in functions except `<cstdlib>`, `<cstdio>`, `<cstring>`, and `<iostream>`.
- No usage of string class, vector, or anything from STL libraries.
- Tree construction time complexity is O(n^2), and space complexity is O(n).
- Search complexity is O(m + occ), where m is the length of the searched pattern, and occ is the number of occurrences of the pattern inside the string.

## Usage

1. Open a C++ compiler.
2. Compile the `suffix_tree.cpp` file.
3. Run the compiled executable.

  ```bash
    g++ suffix_tree.cpp -o suffix_tree
    ./suffix_tree
  ```
## Test Cases
The **main()** function in suffix_tree.cpp includes **10** test cases, each with at least 3 search patterns. Feel free to modify or add more test cases according to your needs.

## Contributors
- This project is maintained by: [Abdelrhman Reda](https://github.com/AbdelrhmanReda17), [Mahmoud Adel](https://github.com/DarkenSoda), [Abdelrhman Atef](https://github.com/AbdoMan19) and [Yassin Tareek](https://github.com/YassinTarekHelmy) 
- Feel free to contribute, report issues, or provide feedback
