# The Goal:

This series of coding projects is designed to experiment with object oriented programming in C++, by following along with the first-year programming courses from the University of Victoria, c. 2013.

# Contents:

Project 1: Linked lists
This project implements a generic linked list class, using a templated class.  The list is doubly-linked, meaning each node in the list has a pointer to both nodes (if they exist) on either side.  The class is also compatible with operators << (outputs a list sequentially to a stream) and == (compares two lists node-by-node).
 Push - pushBack(item) or pushFront(item) inserts the given item into the list at either the tail or head, respectively.
 Pop - popBack() and popFront() removes and returns the item from the tail or head of the list.
 Get Length - getLength() returns the length of the list, which is tracked through all add and remove operations.
 Get - get(int) returns a pointer to the given index, or nullptr if out-of-bounds.
 Find - find(&int, item) searches the list for a copy of the given item, and returns a pointer to it, if it exists. The integer passed as the first argument returns with the index of the found item. If the item was not found, it returns a nullptr and the index is equal to the length of the list.
 Find & Remove - findRemove(item) uses find() to search for the first occurrence of the given item in the list, and if found, removes it. If found, the method returns 1 and 0 otherwise.
 Remove All - removeAll(item) searches the list sequentially and removes all occurrences of the given item, returning the number removed when complete.
 Empty - empty() removes the pointers to the head and tail of the list, effectively flagging it for garbage collection. Also resets the length to 0.

The accompanying LListTest.cpp contains code to automatically test all methods of the linked list class, with either keyboard or file input lists.  All input must be formatted as follows:
 - Each list must occupy one line, and each element must be seperated by whitespace. Each line is turned into an input stream and iteratively attempts to retrieve 'words' from the line and cast them into integers using std::stoi.
 - The reading of an empty line (a line containing only the newline character) safely terminates the creation of the testing lists. The lines are read by calling std::getline on the given input stream (either file or keyboard), and returns errors (as well as an invalid stream object) when encountering an unexpected end of file.
