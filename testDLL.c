/**
 * @file testDLL.c
 * @author Tina Puzzo
 * @date Feb 2023
 *
 * Test and Play to show how the DLL works
 */

#include <stdio.h>
#include <stdlib.h>

#include "DLL.h"

// Printer fucntion (For test we are using ints)
void printInts(int i)
{
    printf("%d", i);
}

// Fucntion to pass in and compare two ints
int compareInts(int d1, int d2)
{

    return (d1 == d2) ? 1 : 0;
}

int main()
{

    printf("TESTS FOR DLL\n");
    printf("------------------\n");

    // Create the Doubly Linked List
    dll_t *d = create_dll();

    // Push New Items to Front
    dll_push_front(d, 3);
    dll_push_front(d, 2);
    dll_push_front(d, 1);
    dll_push_front(d, 0);

    // Push New Items to Back
    dll_push_back(d, 6);
    dll_push_back(d, 7);
    dll_push_back(d, 8);
    dll_push_back(d, 9);

    // Insert items at desired position
    dll_insert(d, 4, 4);
    dll_insert(d, 5, 5);

    // Print Fucntion (proof)
    printf("Printing DLL with ten elements\n");
    printDll(d, printInts);
    printf("Size of dll = %d\n", dll_size(d));

    // Removing and such

    // Removing first
    dll_pop_front(d);
    // Removing last
    dll_pop_back(d);

    // Removing middle
    dll_remove(d, 4);

    // Print Fucntion (proof)
    printf("Printing DLL with 7 elements\n");
    printDll(d, printInts);
    printf("Size of dll = %d\n", dll_size(d));

    printf("\nPrinting results of dll_get\n");
    int i;
    for (i = 0; i < d->count; i++)
    {
        printf("Getting Node at pos %d = %d\n", i, dll_get(d, i));
    }

    printf("\nPrinting results of dll_find (-1 if element not there)\n");
    int j;
    for (j = 0; j < d->count; j++)
    {
        printf("Node with value %d is at pos --> %d\n", j, dll_find(d, j, compareInts));
    }

    // Free DLL
    free_dll(d);
    return 0;
}