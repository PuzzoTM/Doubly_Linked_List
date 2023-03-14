/**
 * @file DLL.c
 * @author Tina Puzo
 * @version 0.2
 * @date Feb 2023
 *
 * Doubly Linked List (Implimented with head/tail sentinals)
 * If you are using/reading this just know... there will be many typos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "DLL.h"

// Added Mutex lock to synchronize access to the linked list
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function Creates node with given data, returns pointer to Node
node_t *createNode(void *data)
{

    // Allocate Memory
    node_t *node = (node_t *)malloc(sizeof(node_t));

    // Check Allocation
    if (node == NULL)
        return NULL;

    // Generic
    node->data = data;

    // Next/Prev pointers
    node->next = NULL;
    node->prev = NULL;

    return node;
}

// Fucntion Creates a DLL, returned pointer to new DLL
dll_t *create_dll()
{

    // Allocate Memeory
    dll_t *myDLL = (dll_t *)malloc(sizeof(dll_t));

    // Check Allocation
    if (myDLL == NULL)
        return NULL;

    // Set count to 0
    myDLL->count = 0;

    // Initlize Head/Tail Sentinels
    myDLL->head = createNode(NULL);
    myDLL->tail = createNode(NULL);

    return myDLL;
}

// Function Checks if the DLL is empty
// Returns -1 if the dll is NULL; 1 if  DLL is completely empty
// Returns 0 if DLL has at least one element enqueued
int dll_isEmpty(dll_t *l)
{

    return (l == NULL) ? -1 : (l->count == 0) ? 1
                                              : 0;
}

// Function pushs a new item to the front of the DLL
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
int dll_push_front(dll_t *l, void *item)
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    node_t *newNode = createNode(item);

    // No items in List
    if (l->count == 0)
    {
        l->head->next = newNode;
        l->tail->prev = newNode;
        newNode->next = l->tail;
        newNode->prev = l->head;
        l->count++;
        pthread_mutex_unlock(&mutex);
        return 1;
    }

    node_t *a = l->head;
    node_t *b = a->next;

    b->prev = newNode;
    newNode->next = b;
    a->next = newNode;
    newNode->prev = a;
    l->count++;

    pthread_mutex_unlock(&mutex);
    return 1;
}

// Fucntion pushs a new item to the end of the DLL
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
int dll_push_back(dll_t *l, void *item)
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    node_t *newNode = createNode(item);

    // If nothing is in the List
    if (l->count == 0)
    {
        // Head and Tail Both point to Node
        l->head->next = newNode;
        l->tail->prev = newNode;
        newNode->next = l->tail;
        newNode->prev = l->head;
        l->count++;

        pthread_mutex_unlock(&mutex);
        return 1;
    }

    node_t *a = l->tail;
    node_t *b = a->prev;

    b->next = newNode;
    newNode->prev = b;
    a->prev = newNode;
    newNode->next = a;
    l->count++;

    pthread_mutex_unlock(&mutex);
    return 1;
}

// Function Removes and Returns the first item in the DLL
// Returns 0 on failure, i.e. there is noting to pop from the list
// Returns -1 if the DLL is NULL.
void *dll_pop_front(dll_t *l)
{

    if (l == NULL)
        return (void *)-1;

    pthread_mutex_lock(&mutex);

    if (dll_isEmpty(l) == 1)
    {
        printf("Nothing to Remove\n");
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    node_t *tmp = l->head->next;
    void *first = tmp->data;

    // Only one item to pop;
    if (l->count == 1)
    {
        l->head->next = NULL;
        l->tail->prev = NULL;

        free(tmp);
        l->count--;
        pthread_mutex_unlock(&mutex);
        return first;
    }

    node_t *a = tmp->next;
    l->head->next = a;
    a->prev = l->head;

    free(tmp);
    l->count--;
    pthread_mutex_unlock(&mutex);
    return first;
}

// Function Removes and Returns the last item in the DLL
// Returns a -1 if the DLL is NULL.
// Returns 0 on failure, i.e. there is noting to pop from the list.
void *dll_pop_back(dll_t *l)
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    if (dll_isEmpty(l) == 1)
    {
        printf("Nothing to Remove");
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    node_t *tmp = l->tail->prev;
    void *last = tmp->data;

    // Onyl one item to pop;
    if (l->count == 1)
    {
        l->head->next = NULL;
        l->tail->prev = NULL;

        free(tmp);
        l->count--;
        pthread_mutex_unlock(&mutex);
        return last;
    }

    node_t *a = tmp->prev;
    l->tail->prev = a;
    a->next = l->tail;

    free(tmp);
    l->count--;
    pthread_mutex_unlock(&mutex);
    return last;
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
int dll_insert(dll_t *l, int pos, void *item)
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    // Impossible Possition
    if ((pos < 0) || (pos > l->count - 1))
    {
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    // First Position
    if (pos == 0)
    {
        pthread_mutex_unlock(&mutex);
        dll_push_front(l, item);
        return 1;
    }

    // Last position
    if (pos == l->count - 1)
    {
        pthread_mutex_unlock(&mutex);
        dll_push_back(l, item);
        return 1;
    }

    // Sandwich Position
    node_t *b = l->head->next;

    int i = 0;
    while (i != pos)
    {
        b = b->next;
        i++;
    }

    node_t *a = b->prev;
    node_t *c = b->next;

    node_t *newNode = createNode(item);
    a->next = newNode;
    newNode->next = b;
    newNode->prev = a;
    b->prev = newNode;

    l->count++;
    pthread_mutex_unlock(&mutex);
    return 1;
}

// Returns the data of Node at position starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure
// [ Note: does not remove item ]
void *dll_get(dll_t *l, int pos)
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    // impossible position
    if ((pos < 0) || (pos > l->count))
    {
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    // Return first  item
    if (pos == 0)
    {
        pthread_mutex_unlock(&mutex);
        return l->head->next->data;
    }

    // Return last item
    if (pos == l->count - 1)
    {
        pthread_mutex_unlock(&mutex);
        return l->tail->prev->data;
    }

    node_t *get = l->head->next;

    int i = 0;
    while (i != pos)
    {
        get = get->next;
        i++;
    }
    pthread_mutex_unlock(&mutex);
    return get->data;
}

// Finds the item by value
// (Passing in compare fucntion dependent on data type)
// Returns -1 if the list is NULL
// Returns 0 on failure:
// Returns pos of item in list upon success
int dll_find(dll_t *l, void *data, int (*compare)(void *d1, void *d2))
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    node_t *cur = l->head->next;

    int i = 0;
    while (cur != l->tail)
    {
        // Get the currents data
        void *cur_data = cur->data;

        // compare currents data to data
        int is_same = compare(data, cur_data);

        // We found so return
        if (is_same == 1)
        {
            pthread_mutex_unlock(&mutex);
            return i;
        }

        // We did not find continue looking
        i++;
        cur = cur->next;
    }

    // We did not find
    pthread_mutex_unlock(&mutex);
    return -1;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
int dll_remove(dll_t *l, int pos)
{

    if (l == NULL)
        return -1;

    pthread_mutex_lock(&mutex);

    if ((pos < 0) || (pos >= l->count))
    {
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    // Remove first
    if (pos == 0)
    {
        pthread_mutex_unlock(&mutex);
        dll_pop_front(l);
        return 1;
    }

    // Remove last
    if (pos == l->count - 1)
    {

        pthread_mutex_unlock(&mutex);
        dll_pop_back(l);
        return 1;
    }

    node_t *b = l->head->next;

    int i = 1;
    while (i != pos + 1)
    {
        b = b->next;
        i++;
    }

    node_t *a = b->prev;
    node_t *c = b->next;

    // [ A ] -> [ B ] -> [ C ]
    // [ A ] <- [ B ] <- [ C ]
    //            ^
    if (a != NULL && c != NULL)
    {
        c->prev = b->prev;
        a->next = b->next;
        free(b);
    }

    l->count--;
    pthread_mutex_unlock(&mutex);
    return 1;
}

// Funtion gets DLL Size
int dll_size(dll_t *l)
{

    return (l == NULL) ? -1 : l->count;
}

// Function prints DLL
// Pass in printer fucntion for specific data type
void printDll(dll_t *l, void (*printer)(void *data))
{

    if (l == NULL)
        return;

    pthread_mutex_lock(&mutex);

    if (dll_isEmpty(l) == 1)
    {
        printf("List is Empty\n");
        return;
    }

    node_t *tmp = l->head->next;
    printf("[");
    while (tmp != l->tail)
    {
        printf(" ");
        // Get the data
        void *item = tmp->data;
        // Call users print function
        (*printer)(item);
        // Point to next
        tmp = tmp->next;
    }
    printf(" ]\n");

    pthread_mutex_unlock(&mutex);
}

// Function Free's DLL
// De-Alloactes DLL and all of its elements from memory
void free_dll(dll_t *l)
{

    pthread_mutex_lock(&mutex);

    if (l == NULL)
    {
        pthread_mutex_unlock(&mutex);
        return;
    }

    node_t *current = l->head;

    while (current != NULL)
    {
        node_t *tmp = current;
        current = current->next;
        free(tmp);
    }

    free(l);
    pthread_mutex_unlock(&mutex);
}
