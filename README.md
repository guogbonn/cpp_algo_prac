# cpp_algo_prac

Daily Algorithm Practice
Arrays
Binary Tree
Dynamic Programming
Linked List
Graphs
Strings

gdb sub. lldb
https://developer.apple.com/library/archive/documentation/IDEs/Conceptual/gdb_to_lldb_transition_guide/document/lldb-command-examples.html
https://lldb.llvm.org/use/tutorial.html#command-structure

tutorial
https://www.youtube.com/watch?v=2GV0K9Y2MKA

compile and run
Debug mode
g++ -std=c++11 -g p.cpp -o r;./r

break set -f p.cpp -l 18
b p.cpp : 27
b dec_5_2021::Node

br list

br del #
br del

p var_name 


frame select // shows where you are at

backtrace with frame select lets you evaluate diffenrent stack
bt
frame select # for short f 0

watch point set var_name
w s v
