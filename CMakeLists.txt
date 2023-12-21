cmake_minimum_required(VERSION 3.24)
project(Advanced_Data_Structures)

set(CMAKE_CXX_STANDARD 14)

include_directories("Suffix Tree")
include_directories("Suffix Tree/SuffixNode")
include_directories("Utilities")
include_directories("Utilities/SingleLinkedList")
include_directories("Utilities/SingleLinkedList/SingleLinkedListNode")

add_executable(Advanced_Data_Structures
        "Suffix Tree/SuffixNode/SuffixNode.cpp"
        "Suffix Tree/SuffixTree.cpp"
        "Utilities/SingleLinkedList/SingleLinkedListNode/SingleLinkedListNode.cpp"
        "Utilities/SingleLinkedList/SingleLinkedList.cpp"
        "Main.cpp")
