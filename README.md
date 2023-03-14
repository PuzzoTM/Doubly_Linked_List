Author: Tina Puzzo
Date: Febuary 2023

Douby Linked List Data Structure

# Steps to compile and run code:

1. run make
2. run ./main

The make file contains the following code instruction: gcc -fsanitize=address -o main DLL.c testDLL.c -I. -pthread

# Overview:

Implementation of a doubly linked list with head/tail sentinels in C.
Uses a mutex lock to synchronize access to the linked list.

The createNode() function creates a new node with the given data and returns a pointer to the new node.

The create_dll() function creates a new doubly linked list with head/tail sentinels and returns a pointer to the new list.

The dll_isEmpty() function checks if the list is empty

- returns -1 if the list is NULL
- 1 if the list is completely empty
- 0 if the list has at least one element.

The dll_push_front() function adds a new item to the front of the list

- returns -1 if the list is NULL
- 1 on success
- 0 on failure (i.e., if memory for the new node could not be allocated).

The dll_push_back() function adds a new item to the end of the list

- returns -1 if the list is NULL
- 1 on success
- 0 on failure (i.e., if memory for the new node could not be allocated).

The dll_pop_front() function removes and returns the first item in the list

- returns 0 on failure (i.e., if there is nothing to pop from the list)
- -1 if the list is NULL.

The dll_pop_back() function removes and returns the last item in the list

- returns -1 if the list is NULL
- 0 on failure (i.e., if there is nothing to pop from the list).

Overall, this program provides a basic set of functions for manipulating a doubly linked list with head/tail sentinels.

# What you should see when you run:

No seg faults hopfully

# Additional Notes:
