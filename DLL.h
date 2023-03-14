/**
 * @file DLL.h
 * @author Tina Puzzo
 * @version 0.2
 * @date Feb 2023
 */

#ifndef MYDLL_H
#define MYDLL_H

// Node Struct
typedef struct node
{
    // Generic Data
    void *data;

    // Pointers
    struct node *next;
    struct node *prev;
} node_t;

// Doubly Linked List Structure
typedef struct DLL
{
    int count;    // keeps track of number of items in the DLL.
    node_t *head; // head sentinel
    node_t *tail; // tail sentinel
} dll_t;

// Function Creates node of given data, returns pointer to new Node
node_t *createNode(void *data);

// Fucntion Creates a DLL, returns pointer to new DLL
dll_t *create_dll();

// Function Checks if the DLL is empty
int dll_isEmpty(dll_t *l);

// Function pushes new item to front of the DLL
int dll_push_front(dll_t *l, void *item);

// Fucntion pushes new item to back of the DLL
int dll_push_back(dll_t *l, void *item);

// Function Removes and Returns first item in the DLL
void *dll_pop_front(dll_t *l);

// Function Removes and Returns last item in the DLL
void *dll_pop_back(dll_t *l);

// Inserts a new node before the node at the specified position
int dll_insert(dll_t *l, int pos, void *item);

// Returns the item at given position ( 0 being the first item )
void *dll_get(dll_t *l, int pos);

// Finds pos of the item in list by given value
// Pass in compare fucntion dependent on data type
int dll_find(dll_t *l, void *data, int (*compare)(void *d1, void *d2));

// Removes the item given position starting ( 0 being the first item )
int dll_remove(dll_t *l, int pos);

// Funtion gets DLL size
int dll_size(dll_t *t);

// Function prints DLL
// Pass in printer fucntion for specific data type
void printDll(dll_t *l, void (*printer)(void *data));

// Function Free's DLL
void free_dll(dll_t *l);

#endif